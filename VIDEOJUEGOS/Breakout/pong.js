/*
 * Using sprites to draw more interesting objects
 *
 * Gilberto Echeverria
 * 2025-03-13
 */

"use strict";

// canvas size
const canvasWidth = 800;
const canvasHeight = 600;

// Context of the Canvas
let ctx;

// main game object
let game;

// time tracking for deltaTime
let oldTime = 0;

// speeds
let paddleSpeed = 0.5;
let ballSpeed = 0.5;


// helper to draw text on screen (score + lives)
class TextLabel {
    constructor(x, y, font, color) {
        this.x = x;
        this.y = y;
        this.font = font;
        this.color = color;
    }

    draw(ctx, text) {
        ctx.fillStyle = this.color;
        ctx.font = this.font;
        ctx.textAlign = "center";
        ctx.fillText(text, this.x, this.y);
    }
}


// Ball class handles movement, serving, and reset
class Ball extends GameObject {
    constructor(position, width, height, color) {
        super(position, width, height, color, "ball");

        this.directionX = 0;
        this.directionY = 0;
        this.velocity = new Vector(0, 0);

        this.setSprite("assets/SoccerBall.png");
    }

    update(deltaTime) {
        // normalize direction so speed is consistent
        this.velocity = new Vector(this.directionX, this.directionY)
            .normalize()
            .times(ballSpeed);

        this.position = this.position.plus(this.velocity.times(deltaTime));
        this.updateCollider();
    }

    reset() {
        // reset ball to center and stop movement
        this.position = new Vector(canvasWidth / 2, canvasHeight / 2);
        this.directionX = 0;
        this.directionY = 0;
        ballSpeed = 0.5;
        this.updateCollider();
    }

    serve() {
        // random angle so gameplay isn't predictable
        let angle = Math.random() * Math.PI / 2 - (Math.PI / 4);
        this.directionX = Math.cos(angle);
        this.directionY = Math.sin(angle);

        // randomly go left or right
        if (Math.random() > 0.5) this.directionX *= -1;

        // always go upward on serve
        this.directionY = -Math.abs(this.directionY);

        ballSpeed = 0.5;
    }
}


// Brick class (destructible objects)
class Brick extends GameObject {
    constructor(position, width, height) {
        super(position, width, height, "brown", "brick");
        this.active = true;

        this.setSprite("assets/RTS_Crate.png");
    }

    draw(ctx) {
        // only draw if still active
        if (this.active) super.draw(ctx);
    }

    update() {
        this.updateCollider();
    }
}


// Paddle class handles player input and movement
class Paddle extends GameObject {
    constructor(position, width, height, color) {
        super(position, width, height, color, "paddle");

        this.velocity = new Vector(0, 0);

        // maps movement directions
        this.motion = {
            left:  { axis: "x", sign: -1 },
            right: { axis: "x", sign:  1 },
        };

        // keys currently being pressed
        this.keys = [];
    }

    update(deltaTime) {
        // reset velocity each frame
        this.velocity.x = 0;
        this.velocity.y = 0;

        for (const direction of this.keys) {
            const axis = this.motion[direction].axis;
            const sign = this.motion[direction].sign;
            this.velocity[axis] += sign;
        }

        // normalize so diagonal doesn't increase speed
        this.velocity = this.velocity.normalize().times(paddleSpeed);

        this.position = this.position.plus(this.velocity.times(deltaTime));

        this.clampWithinCanvas();
        this.updateCollider();
    }

    clampWithinCanvas() {
        // prevent leaving screen horizontally
        if (this.position.x - this.halfSize.x < 0)
            this.position.x = this.halfSize.x;

        if (this.position.x + this.halfSize.x > canvasWidth)
            this.position.x = canvasWidth - this.halfSize.x;
    }
}


// Flashbang effect (screen flash when scoring)
class Flashbang {
    constructor() {
        this.alpha    = 0;
        this.active   = false;
        this.duration = 6000;
        this.elapsed  = 0;
    }

    trigger() {
        this.alpha   = 0.5;
        this.active  = true;
        this.elapsed = 0;
    }

    update(deltaTime) {
        if (!this.active) return;

        this.elapsed += deltaTime;

        // fade out effect
        this.alpha = Math.max(0, 1 - this.elapsed / this.duration);

        if (this.alpha <= 0) this.active = false;
    }

    draw(ctx) {
        if (!this.active) return;

        ctx.save();
        ctx.globalAlpha = this.alpha;
        ctx.fillStyle   = "white";
        ctx.fillRect(0, 0, canvasWidth, canvasHeight);
        ctx.restore();
    }
}


// Main Game class (controls everything)
class Game {
    constructor() {
        this.points   = 0;
        this.lives    = 3;
        this.gameOver = false;

        this.lastFlashThreshold = 0;
        this.flash = new Flashbang();

        this.createEventListeners();
        this.initObjects();
    }

    initObjects() {
        // background
        this.background = new GameObject(
            new Vector(canvasWidth / 2, canvasHeight / 2),
            canvasWidth,
            canvasHeight,
            "#1a1a2e"
        );

        // player paddle
        this.paddleBottom = new Paddle(
            new Vector(canvasWidth / 2, canvasHeight - 20),
            120,
            20,
            "red"
        );

        // ball
        this.ball = new Ball(
            new Vector(canvasWidth / 2, canvasHeight / 2),
            20,
            20,
            "white"
        );

        // walls
        this.top_wall    = new GameObject(new Vector(canvasWidth / 2, 1), canvasWidth, 10, "gray");
        this.left_wall   = new GameObject(new Vector(1, canvasHeight / 2), 10, canvasHeight, "gray");
        this.right_wall  = new GameObject(new Vector(canvasWidth - 1, canvasHeight / 2), 10, canvasHeight, "gray");
        this.bottom_wall = new GameObject(new Vector(canvasWidth / 2, canvasHeight - 1), canvasWidth, 10, "gray");

        this.top_wall.updateCollider();
        this.left_wall.updateCollider();
        this.right_wall.updateCollider();
        this.bottom_wall.updateCollider();

        // bricks grid
        this.bricks = [];
        const cols = 10, rows = 5;

        const brickW = 70, brickH = 25;
        const paddingX = 10, paddingY = 10;
        const offsetTop = 80;
        const offsetLeft =
            (canvasWidth - (cols * (brickW + paddingX) - paddingX)) / 2;

        for (let row = 0; row < rows; row++) {
            for (let col = 0; col < cols; col++) {
                const x = offsetLeft + col * (brickW + paddingX) + brickW / 2;
                const y = offsetTop  + row * (brickH + paddingY) + brickH / 2;

                this.bricks.push(new Brick(new Vector(x, y), brickW, brickH));
            }
        }

        
        this.pointsText = new TextLabel(canvasWidth / 2, 50, "30px monospace", "white");
        this.livesText  = new TextLabel(80, 50, "30px monospace", "white");
    }

    addPoints(amount) {
        this.points += amount;

        // trigger flash every n points this case 3 
        const threshold = Math.floor(this.points / 3) * 3;

        if (threshold > this.lastFlashThreshold && threshold > 0) {
            this.lastFlashThreshold = threshold;
            this.flash.trigger();
        }
    }

    draw(ctx) {
        this.background.draw(ctx);

        for (const brick of this.bricks) brick.draw(ctx);

        this.paddleBottom.draw(ctx);
        this.ball.draw(ctx);

        this.top_wall.draw(ctx);
        this.left_wall.draw(ctx);
        this.right_wall.draw(ctx);
        this.bottom_wall.draw(ctx);

        this.pointsText.draw(ctx, "Score: " + this.points);
        this.livesText.draw(ctx, "Lives: " + this.lives);

        this.flash.draw(ctx);

        if (this.gameOver) this.drawGameOver(ctx);
    }

    // game over screen
    drawGameOver(ctx) {
        ctx.fillStyle = "rgba(0, 0, 0, 0.6)";
        ctx.fillRect(0, 0, canvasWidth, canvasHeight);

        ctx.fillStyle = "red";
        ctx.font = "bold 80px monospace";
        ctx.textAlign = "center";
        ctx.fillText("GAME OVER", canvasWidth / 2, canvasHeight / 2 - 20);

        ctx.fillStyle = "white";
        ctx.font = "30px monospace";
        ctx.fillText("Score: " + this.points, canvasWidth / 2, canvasHeight / 2 + 40);

        ctx.font = "20px monospace";
        ctx.fillText("Press SPACE to play again", canvasWidth / 2, canvasHeight / 2 + 90);
    }
}

