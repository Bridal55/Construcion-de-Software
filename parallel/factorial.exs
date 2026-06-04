#Julian Berges A01787490
#ELixir parallel
# :timer.tc(fn -> ParallelFactorial.factorial(100, 10)end)
# :timer.tc(fn -> ParallelFactorial.factorial(10)end) |> elem(0) |> Kernel./(1_000_000) this is for conversion into seconds

defmodule ParallelFactorial do

  def factorial(n), do: factorial_range({1,n})

  def factorial_range({start,stop}) do
    Enum.reduce(start..stop,1,&(&1 * &2))
  end

  def factorial_parallel(n,tasks \\ System.schedulers) do


    step = ceil(n / tasks)
    starts = [1 | Enum.to_list(step + 1 .. n//step)]
    finishes = Enum.map(starts , fn start -> min(start + step - 1, n)end)


    Enum.zip(starts,finishes)
    |> IO.inspect()
    |> Enum.map(&Task.async(fn -> factorial_range(&1) end)) # parallel part
    |> Enum.map(&Task.await(&1, :infinity)) # waits for the task to finished, defualt time 5ms
    |> Enum.reduce(1,&(&1 * &2))

  end
end
