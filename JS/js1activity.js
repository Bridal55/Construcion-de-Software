/*
 * Example functions to practice JavaScript
 *
 * Gilberto Echeverria
 * 2025-02-12
 */

"use strict";

function firstNonrepeating(str) {
    const candidates = [];
    
    for(let  i = 0; i <str.length; i++){
        
        let found = false;
        for (let cand of candidates){
            if (cand.char == str[i]){
                cand.count += 1;
                found = true;
            }
        }

        if (!found){
            candidates.push({char: str[i],count:1});
        }
    }
        for (let index in candidates){
            if(candidates[index].count == 1){
                return candidates[index].char;
                
            }
        }
            
}


function bubbleSort(arr) {
    const n = arr.slice(); 

    for (let end = n.length - 1; end > 0; end--){
        let swapped = false;

        for (let i = 0; i < end; i++) {
            if (n[i] > n[i + 1]) {
                const j = n[i];
                n[i] = n[i + 1];
                n[i + 1] = j;
                swapped = true;
            }
        }

        if (!swapped) 
        break;
    }
    return n;
}


function invertArray(arr){
    const x = [];
    for (let i = arr.length - 1; i >= 0; i--) {
        x.push(arr[i]);
    }
    return x;
}

function invertArrayInplace(arr) {
    let left = 0;
    let right = arr.length - 1;

    while (left < right) {
        const tmp = arr[left];
        arr[left] = arr[right];
        arr[right] = tmp;

        left++;
        right--;
    }
}


function capitalize(str){
    let new_str = "";
    let size = str.length;
    let next;
    new_str = new_str + str.charAt(0).toUpperCase();
    for(let i = 1; i < size; i++){
        
        if(str.at(i) == " "){
            next = str.charAt(i+1);
            new_str = new_str + str.charAt(i)+ next.toUpperCase();
        }
        else{
            if(str.at(i) == next){
                new_str = new_str + "";
            }
            else{
                new_str = new_str + str.charAt(i);
            }
        }
    }
    return new_str;
}

function mcd(a, b) {
    a = Math.abs(a);
    b = Math.abs(b);

    if (a === 0 && b === 0) 
    return 0;

    while (b !== 0) {
        const result = a % b;
        a = b;
        b = result;
    }
    return a;
}


function hackerSpeak(str) {
    const map = {
        a: "4",
        e: "3",
        i: "1",
        o: "0",
        s: "5",
    };

    let HS_str = "";
    for (let i = 0; i < str.length; i++) {
        const char = str[i];
        const lower = char.toLowerCase();
        if (map[lower] !== undefined) {
        HS_str += map[lower];
        } 
        else {
            HS_str += char;
        }
    }
    return HS_str;
}


function factorize(x){
    let arr = [];
    for (let i = 1; i <= x; i++){
        if (x%i === 0){
            arr.push(i)
        }
    }

    return arr;
}


function deduplicate(arr) {
    const out = [];
    const seen = new Set();

    for (let i = 0; i < arr.length; i++) {
        const v = arr[i];
        if (!seen.has(v)) {
            seen.add(v);
            out.push(v);
        }
    }
    return out;
}


function findShortestString(list) {
    if (list.length === 0) 
    return 0;

    let minlen = list[0].length;
    for (let i = 1; i < list.length; i++) {
        if (list[i].length < minlen) minlen = list[i].length;
    }
    return minlen;
}


function isPalindrome(str) {
    let left = 0;
    let right = str.length - 1;

    while (left < right) {
        if (str[left] !== str[right]) 
        return false;
        
        left++;
        right--;
    }
    return true;
}


function sortStrings(arr) {
    const sorted_str = arr.slice();
    sorted_str.sort(); 
    return sorted_str;
} 


function stats(nums) {
    if (nums.length === 0) 
    return [0, 0];

    let sum = 0;
    for (let i = 0; i < nums.length; i++) 
    sum += nums[i];

    const avg = sum / nums.length;

    
    const counts = new Map();
    let mode = nums[0];
    let best = 0;

    for (let i = 0; i < nums.length; i++) {
    const value = nums[i];

    let prev = counts.get(value);

    
    if (prev === undefined) {
        prev = 0;
    }

    const count = prev + 1;

    counts.set(value, count);

    if (count > best) {
        best = count;
        mode = value;
    }
    return [avg, mode];
}
}


function popularString(list) {

    if (list.length === 0) {
        return "";
    }

    const counts = {};
    let bestStr = list[0];
    let bestCount = 0;

    for (let i = 0; i < list.length; i++) {

        const s = list[i];

        if (counts[s] === undefined) {
            counts[s] = 1;
        } else {
            counts[s] = counts[s] + 1;
        }

        if (counts[s] > bestCount) {
            bestCount = counts[s];
            bestStr = s;
        }
    }

    return bestStr;
}


function isPowerOf2(n) {
    if(n==0)
    return false;
    if (n < 1) 
    return false;

    while (n % 2 === 0 ) {
        n = n / 2;
    }
    return n === 1;
}


function sortDescending(arr) {
}



export {
    firstNonrepeating,
    bubbleSort,
    invertArray,
    invertArrayInplace,
    capitalize,
    mcd,
    hackerSpeak,
    factorize,
    deduplicate,
    findShortestString,
    isPalindrome,
    sortStrings,
    stats,
    popularString,
    isPowerOf2,
    sortDescending,
};
