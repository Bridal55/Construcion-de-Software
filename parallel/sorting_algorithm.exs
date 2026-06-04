#Julian berges |A01787490
#Merge sort by Ch Virinchi (sorry sir i just didnt had the time my b)



defmodule MergeSort do
  def sort([]), do: []
  def sort([x]), do: [x]

  def sort(list) do
    midpoint = div(length(list), 2)
    {left, right} = Enum.split(list, midpoint)
    merge(sort(left), sort(right))
  end

  def merge(left, []), do: left
  def merge([], right), do: right

  def merge([l | left], [r | right]) when l <= r do
    [l | merge(left, [r | right])]
  end

  def merge([l | left], [r | right]) do
    [r | merge([l | left], right)]
  end

  def merge_parallel(list, tasks \\ System.schedulers()) do
    step = ceil(length(list) / tasks)

    list
    |> Enum.chunk_every(step) #chunk every make a list of lists with the size of step
    |> Enum.map(&Task.async(fn -> sort(&1) end))
    |> Enum.map(&Task.await(&1, :infinity))
    |> Enum.reduce([], &merge/2) # this is the merge part, it merges the sorted lists into one sorted list jupi
  end
end
