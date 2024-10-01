(use 'clojure.math)
(use 'clojure.edn)
(use '[clojure.string :only (split)])

(defn read-input [file] (-> file slurp (#(split % #"\n")) (#(map read-string %))))
(defn fuel [n] (-> n (#(/ % 3)) floor (#(- % 2))))
(defn solve [file] (-> file read-input (#(map fuel %)) (#(reduce + %))))
