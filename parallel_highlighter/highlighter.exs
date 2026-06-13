#Syntax highlighter
#Julian bereges N | A01787490
#FileHighlighter.measure_time(fn input, output, t -> FileHighlighter.highlight_parallel(input, output, t) end,["cpp_files", "output", 4])




defmodule CppLexer do

  @keywords ~w( int float double char bool void if else while for do switch case break return class namespace public private new delete nullptr true false this const  auto)


  def do_allsyntax(source) do
    source
    |> tokenize([])
    |> html()
  end

  def do_syntax(source) do
    tokens = tokenize(source, [])
    html   = html(tokens)
    File.write!("output.html", html)
    IO.puts("Done -> output.html")
  end



  def tokenize("", acc), do: Enum.reverse(acc)

  def tokenize(source, acc) do
    {type, value, rest} = next_token(source)
    tokenize(rest, [{type, value} | acc])
  end



  defp next_token(source) do
    cond do

      # space
      m = match(source, ~r/^\s+/) ->
        {:space, m, drop(source, m)}

      # Multi line comment
      m = match(source, ~r/^\/\*[\s\S]*?\*\//) ->
        {:comment_multi, m, drop(source, m)}

      # Single-line comment
      m = match(source, ~r/^\/\/[^\n]*/) ->
        {:comment_single, m, drop(source, m)}

      # Preprocessor directive
      m = match(source, ~r/^#[#[a-zA-Z_][a-zA-Z0-9_]*[^\n]*/) ->
        {:preprocessor, m, drop(source, m)}

      # String literal
      m = match(source, ~r/^"([^"\\]|\\.)*"/) ->
        {:string, m, drop(source, m)}

      # Char literal
      m = match(source, ~r/^'([^'\\]|\\[0-9a-fA-F]{1,3}|\\.)'/) ->
        {:char, m, drop(source, m)}

      # Float
      m = match(source, ~r/^\d*\.\d+([eE][+-]?\d+)?[fFlL]?|^\d+[eE][+-]?\d+[fFlL]?/) ->
        {:float, m, drop(source, m)}

      # Integer
      m = match(source, ~r/^\d+[uUlL]*/) ->
        {:integer, m, drop(source, m)}

      # Keyword or variable
      m = match(source, ~r/^[a-zA-Z_][a-zA-Z0-9_]*/) ->
        type = if m in @keywords, do: :reserved, else: :variable
        {type, m, drop(source, m)}

      # Assignment
      m = match(source, ~r/^(<<=|>>=|[+\-*\/%&|^]=|=(?!=))/) ->
        {:op_assign, m, drop(source, m)}

      # Comparison
      m = match(source, ~r/^(<=>|<=|>=|==|!=|[<>])/) ->
        {:op_comparison, m, drop(source, m)}

      # Logical
      m = match(source, ~r/^(&&|\|\||!)/) ->
        {:op_logical, m, drop(source, m)}

      # Arithmetic
      m = match(source, ~r/^(\+\+|--|[+\-*\/%])/) ->
        {:op_arithmetic, m, drop(source, m)}

      # Punctuation
      m = match(source, ~r/^[{}\[\]();,:.]/) ->
        {:punctuation, m, drop(source, m)}

      # Unknown
      true ->
        <<ch::utf8, rest::binary>> = source
        {:unknown, <<ch::utf8>>, rest}
    end
  end



  defp match(source, regex) do
    case Regex.run(regex, source) do
      [head | _] -> head
      nil        -> nil
    end
  end

  defp drop(source, matched) do
    String.slice(source, String.length(matched)..-1//1)
  end

  defp html(tokens) do
    body =
      tokens
      |> Enum.map(fn {type, value} ->
        "<span class=\"#{type}\">#{html_escape(value)}</span>"
      end)
      |> Enum.join("")

    """
    <!DOCTYPE html>
    <html lang="en">
    <head>
      <meta charset="UTF-8">
      <title>Lexer Output of C++ files </title>
      <style>
        body             { background: #1e1e1e; color: #d4d4d4; font-family: monospace;
                           font-size: 14px; padding: 2rem; white-space: pre-wrap; }
        .reserved        { color: #569cd6; font-weight: bold; }
        .variable        { color: #9cdcfe; }
        .integer         { color: #b5cea8; }
        .float           { color: #b5cea8; }
        .string          { color: #ce9178; }
        .char            { color: #ce9178; }
        .comment_single  { color: #6a9955; font-style: italic; }
        .comment_multi   { color: #6a9955; font-style: italic; }
        .op_arithmetic   { color: #d4d4d4; }
        .op_assign       { color: #d4d4d4; }
        .op_comparison   { color: #d4d4d4; }
        .op_logical      { color: #d4d4d4; }
        .punctuation     { color: #808080; }
        .preprocessor    { color: #c586c0; }
        .space           { }
        .unknown         { color: #f44747; text-decoration: underline; }
      </style>
    </head>
    <body><pre>#{body}</pre></body>
    </html>
    """
  end

  defp html_escape(str) do
    str
    |> String.replace("&", "&amp;")
    |> String.replace("<", "&lt;")
    |> String.replace(">", "&gt;")
  end

end


defmodule FileHighlighter do

  defp list_files(folder) do # list all files of the folder into a path
    folder
    |> File.ls!()
    |> Enum.map(&Path.join(folder, &1))
  end

  defp process_file(folder_path, output) do # makes the tokenizser and highlighter for each file
    basename = Path.basename(folder_path, Path.extname(folder_path))
    out_path = Path.join(output, basename <> ".html")

    folder_path
    |> File.read!()
    |> CppLexer.do_allsyntax()
    |> then(&File.write!(out_path, &1))

    IO.puts("Done -> #{out_path}")
  end

  def highlight_parallel(input_folder, output_folder, tasks \\ System.schedulers()) do #parallel function for multi files
    File.mkdir_p!(output_folder)

    files = list_files(input_folder)
    step = ceil(length(files) / tasks)
    results =
      files
      |> Enum.chunk_every(step)
      |> Enum.map(fn chunk ->
        Task.async(fn -> Enum.map(chunk, &process_file(&1, output_folder))end)
      end)

      |> Enum.map(&Task.await(&1, :infinity))
      |> List.flatten()

  end

    def measure_time(function, parameters) do # time function, helper for command prompt
    {time, _result} = :timer.tc(function, parameters)
    time / 1_000_000
  end

end
