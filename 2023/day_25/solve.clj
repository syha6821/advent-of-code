(use '[clojure.string :only (split includes? trim replace ends-with? starts-with? replace-first join)])
(use '[clojure.string :only (split includes? trim replace ends-with? starts-with? replace-first join)])
(use '[clojure.math :only (sqrt pow)])
(use '[clojure.set :only (intersection union rename-keys rename difference subset? superset?)])
(use '[clojure.spec.alpha :only (int-in-range?)])


(def input (split (slurp "./input.txt") #"\n"))
(def sample (split (slurp "./sample.txt") #"\n"))

(defn read-line [line]
(let [s (split line #":")]
    {(first s) (into #{} (remove empty? (split (second s) #" ")))}))

(defn read-input [input]
(let [input (into {} (map read-line input))]
    (reduce (fn [result [k vals]]
            (reduce (fn [r v] (update-in r [v] (fnil conj #{}) k)) result vals)) input input)))

(defn make-wire [m1 m2]
#{m1 m2})

(defn make-group-from [machine machines machine-map]
(if (empty? machines)
    #{machine}
    (let [connected (intersection machines (machine-map machine))
        current-group (conj connected machine)
        next-machines (difference machines current-group)]
    (:group (reduce (fn [{group :group done :done} m]
                        (let [next-group (union group (make-group-from m (difference next-machines done) machine-map))]
                        {:group next-group :done (union done next-group)}))
                    {:group current-group :done #{}} connected)))))

(defn group [machines machine-map]
(loop [machines machines
        result #{}]
    (if (empty? machines)
    result
    (let [machine (first machines)
            group (make-group-from (first machines) (disj machines machine) machine-map)]
        (recur (apply disj machines group)
                (conj result group))))))

(defn child-of-group [group machine-map]
(reduce (fn [result machine] (union result (difference (machine-map machine) group))) #{} group))

(defn wires-between [top-group bottom-group machine-map]
(reduce (fn [result machine] (union result
                                    (into #{} (map #(make-wire % machine) (filter #(contains? (machine-map %) machine) top-group))))) #{} bottom-group))

(defn remove-trace-of [machine machine-map]
(dissoc (reduce (fn [result m] (update result m disj machine)) machine-map (machine-map machine)) machine))

(defn all-items-of [sets]
(reduce (fn [result s] (union result s)) #{} sets))

(defn connect-by-wire [parent children machine-map]
(reduce (fn [result child] (assoc result (wires-between parent child machine-map) {:child child :parent parent})) {} children))

(defn hang-down [top machines]
(loop [machine-map machines
        parent-map {#{top} #{}}
        groups #{#{top}}
        height 0
        result {}]
    (if (empty? machine-map)
    result
    (let [next-machines (reduce (fn [result g] (union result (child-of-group g machine-map))) #{} groups)
            next-groups (group next-machines machine-map)
            next-hash-map (zipmap (map hash next-groups) next-groups)
            connects (reduce (fn [result g] (assoc result g (connect-by-wire g next-groups machine-map))) {} groups)
            result (-> result
                        (assoc-in [height :group-map]
                                (reduce (fn [result g] (assoc result g
                                                                {:parents (parent-map g)
                                                                :children (into #{} (map :child (map val (connects g))))})) {} groups))
                        (assoc-in [height :wire-map] (reduce (fn [result m] (into result m)) {} (map val connects))))]
        (recur (reduce (fn [result i] (remove-trace-of i result)) machine-map (all-items-of groups))
                (reduce (fn [result {child :child parent :parent}] (update-in result [child] (fnil conj #{}) parent)) {} (map val (:wire-map (result height))))
                next-groups
                (inc height)
                result)))))

(defn hang-down-from-group [g machines]
(loop [machine-map machines
        parent-map {#{g} #{}}
        groups #{g}
        height 0
        result {}]
    (if (empty? machine-map)
    result
    (let [next-machines (reduce (fn [result g] (union result (child-of-group g machine-map))) #{} groups)
            next-groups (group next-machines machine-map)
            next-hash-map (zipmap (map hash next-groups) next-groups)
            connects (reduce (fn [result g] (assoc result g (connect-by-wire g next-groups machine-map))) {} groups)
            result (-> result
                        (assoc-in [height :group-map]
                                (reduce (fn [result g] (assoc result g
                                                                {:parents (parent-map g)
                                                                :children (into #{} (map :child (map val (connects g))))})) {} groups))
                        (assoc-in [height :wire-map] (reduce (fn [result m] (into result m)) {} (map val connects))))]
        (recur (reduce (fn [result i] (remove-trace-of i result)) machine-map (all-items-of groups))
                (reduce (fn [result {child :child parent :parent}] (update-in result [child] (fnil conj #{}) parent)) {} (map val (:wire-map (result height))))
                next-groups
                (inc height)
                result)))))

(defn find-bottom-machines [hang]
(reduce (fn [result [height {group-map :group-map}]]
            (let [bottoms (filter (fn [[group {children :children}]] (empty? children)) group-map)]
            (if bottoms
                (union result (into #{} (map #(hash-map :height height :machine (key %)) bottoms)))
                result))) #{} hang))

(defn has-the-three-wires? [start-machine start-height hang]
(loop [height start-height
        machines #{start-machine}]
    (if (zero? height)
    false
    (let [wire-groups (map key (filter (fn [[wire {child :child}]] (contains? machines child)) (:wire-map (hang (dec height)))))]
        (cond (= 3 (reduce (fn [result wire-group] (+ result (count wire-group))) 0 wire-groups))
            (reduce (fn [result wire-group] (union result wire-group)) #{} wire-groups)
            :else (recur (dec height)
                        (into #{} (map key (filter (fn [[machine {children :children}]] (some #(contains? children %) machines)) (:group-map (hang (dec height))))))))))))

(defn find-the-three-wires [hang]
(some (fn [{machine :machine height :height}] (has-the-three-wires? machine height hang)) (find-bottom-machines hang)))

(defn all-wires [machine-map]
(reduce (fn [result [machine connects]] (into result (map #(make-wire % machine) connects))) #{} machine-map))

(defn solve [input]
(let [machine-map (read-input input)
        hangs (map #(hang-down % machine-map) (map key machine-map))
        three-wires (some find-the-three-wires hangs)
        k (println three-wires)
        groups (group (into #{} (map key machine-map))
                    (reduce (fn [result wire] (-> result
                                                    (update-in [(first wire)] disj (second wire))
                                                    (update-in [(second wire)] disj (first wire))))
                            machine-map three-wires))]
    (* (count (first groups))
        (count (second groups)))))

(defn solve-2 [input]
(let [machine-map (read-input input)
        hangs (map #(hang-down-from-group % machine-map) (all-wires machine-map))
        three-wires (some find-the-three-wires hangs)
        k (println three-wires)
        groups (group (into #{} (map key machine-map))
                    (reduce (fn [result wire] (-> result
                                                    (update-in [(first wire)] disj (second wire))
                                                    (update-in [(second wire)] disj (first wire))))
                            machine-map three-wires))]
    (* (count (first groups))
        (count (second groups)))))

(has-the-three-wires? #{"rhn" "ntq" "xhk"} 4 (hang-down "frs" (read-input sample)))

(def sample-hangs (let [input (read-input sample)] (map #(hang-down % input) (map key input))))
(def input-hangs (let [input (read-input input)] (map #(hang-down % input) (map key input))))
(map (fn [[_ {groups :group-map}]] (map #(count (key %)) groups)) (hang-down "frs" (read-input sample)))
(map (fn [[_ {groups :group-map}]] (count groups)) (hang-down "frs" (read-input sample)))
