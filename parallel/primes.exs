# Julian berges | A01787490
# Elixir parallel
# timer.tc(fn -> ParallelFactorial.factorial(100, 10)end)

 
defmodule Primes do
  def is_prime (x) do
    cond do
      x < 2  -> false
      x == 2 -> true
    true ->
     limit = x
     |> :math.sqrt()
     |> ceil()
     not Enum.any?(2..limit, fn i -> rem(x, i) == 0 end)
    end
  end

  def sum_primes(n) do
      1..n
      |> Enum.filter(&is_prime/1)
      |> Enum.sum()
    end

  def prime_range({start,stop}) do
      start..stop
      |> Enum.filter(&is_prime/1)
      |> Enum.sum()
  end


  def prime_parallel(n,tasks \\ System.schedulers) do


    step = ceil(n / tasks)
    starts = Enum.to_list(1 .. n//step)
    finishes = Enum.map(starts , fn start ->min(start + step - 1, n)end)


    Enum.zip(starts,finishes)
    |> IO.inspect()
    |> Enum.map(&Task.async(fn -> prime_range(&1) end)) # parallel part
    |> Enum.map(&Task.await(&1, :infinity)) # waits for the task
    |> Enum.sum()


  end
end

















# bool is_prime(int x) {

#     if (x < 2) return false;
#     if (x == 2) return true;

#     int limit = (int)ceil(sqrt((double)x));

#     for (int i = 2; i <= limit; i++) {
#         if (x % i == 0) return false;
#     }
#     return true;
# }

# int sum_primes(int n ){

#     int total = 0;
#     for (int x = 2; x <= n; x++) {
#         if (is_prime(x)) {
#             total += x;
#         }
#     }
#     return total;

# }
