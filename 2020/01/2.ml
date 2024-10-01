module IntSet = Set.Make(Int)

let read_lines file =
  In_channel.with_open_text file In_channel.input_all
  |> String.trim
  |> String.split_on_char '\n'
  |> List.map int_of_string

(* let rec find_match list = *)
(*   let numbers = IntSet.of_list list in  *)
(*   match list with *)
(*   | [] -> None *)
(*   | h :: t -> begin *)
(*       if IntSet.mem (2020 - h) numbers then Some (h,2020-h) else *)
(*         find_match t *)
(*     end *)

let find_match list =
  let rec find list goal =
  let numbers = IntSet.of_list list in 
  match list with
  | [] -> None
  | h :: t -> begin
      if IntSet.mem (2020 - h) numbers then Some (h,2020-h) else
        find_match t
    end

let solve file =
  let result = read_lines file |> find_match in
  match result with
  | Some (f,s) -> Some (f * s)
  | _ -> None
