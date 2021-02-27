;8. Return the list of nodes of a tree of type (2) accessed inorder

;inorder(l1l2l3..ln) = l1, n=1
;                      inorder(l2) U l1, n=2
;                      inorder(l2) U l1 U inorder(l3) , otherwise

;(load "a6_8.lisp")

(defun inorder(L)
    (cond 
        ((equal (cdr L) nil)
            L
        )
        (t
            (append 
                (append 
                    (inorder (car (cdr L))) 
                    (list (car L))
                ) 
                (inorder (car (cdr (cdr L)))) 
            )
        ) 
    )
)

;(inorder '(1 (2 (4) (5 (6 (8) ) (7) ) ) (3) ))
