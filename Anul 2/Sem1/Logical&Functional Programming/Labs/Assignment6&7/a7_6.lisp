;6. Write a function that returns the maximum of numeric atoms in a list, at any level


; maximumAtom(l) = l, l is a number 
;                  0, l is an atom 
;                  max(maximumAtom(list_i)) i=1...n, otherwise

;(load "a7_6.lisp")

(defun maximumAtom(l) 
    (cond 
        ((numberp l) l) 
        ((atom l) 0) 
        (t 
            (apply #'max (mapcar #'maximumAtom l))
        ) 
    )
) 

;(maximumAtom '(1 2 (1 A (B 15 (81) 9) ) 3 (F (8 (82( ( (83) ) ) ) ) ) 4 500 6 7))