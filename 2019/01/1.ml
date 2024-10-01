open Core

let read_input file =
  file
  |> In_channel.read_lines
  |> List.map ~f:int_of_string

let fuel n =
  n
  |> (fun n -> n / 3)
  |> (fun n -> n - 2)

let solve file =
  file
  |> read_input
  |> List.map ~f:fuel
  |> List.sum (module Int) ~f:Fn.id

