#Julian Berges A01787490
#Inegracion de pi
# timer.tc(fn -> ParallelFactorial.factorial(100, 10)end)
# timer.tc(fn -> ParallelFactorial.factorial(10)end) |> elem(0) |> Kernel./(1_000_000) this is for conversion into seconds


defmodule Num_integration do
    def compute_pi(n) do

        width = 1.0 / n
        sum = Enum.reduce(0..(n - 1), 0.0, fn i, sum1 ->

            mid = (i + 0.5) * width
            height = 4.0 / (1.0 + mid * mid)
            sum1 + height
        end
        )

        width * sum
        # |> Float.round(15)
    end

    def pi_range({start, stop}, n) do

        width = 1.0 / n
        Enum.reduce(start..stop, 0.0, fn i, sum ->
            mid = (i + 0.5) * width
            height = 4.0 / (1.0 + mid * mid)
            sum + height
        end
        )
  end

    def numint_parallel(n,tasks \\ System.schedulers) do

    step = ceil(n / tasks)
    starts = Enum.to_list(0..(n - 1)//step)
    finishes = Enum.map(starts, fn s -> min(s + step - 1, n - 1) end) # min is for the last real value

    Enum.zip(starts,finishes)
    |> IO.inspect()
    |> Enum.map(&Task.async(fn -> pi_range(&1,n) end)) # parallel part
    |> Enum.map(&Task.await(&1, :infinity)) # waits for the task to finished, defualt time 5ms
    |> Enum.sum()
    |> Kernel.*(1.0 / n)

  end
end


# 3.14159265358979323846 pi 

# double compute_pi(long n) {
#     double sum = 0.0;
#     double width = 1.0 / n;
#     for (long i = 0; i < n; i++) {
#     double mid = (i + 0.5) * width;
#     double height = 4.0 / (1.0 + mid * mid);
#     sum += height;
#     }
#     return width * sum;
# }
