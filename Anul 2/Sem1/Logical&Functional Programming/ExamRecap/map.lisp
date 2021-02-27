;; (defun CountEven(tree lvl) 
;;     (cond 
;;         (
;;             (and 
;;                 (atom tree) 
;;                 (evenp lvl)
;;             )
;;             1
;;         ) 

;;         ((atom tree) 
;;             0
;;         ) 

;;         (t 
;;             (apply 
;;                 #’+
;;                 (mapcar #’(lambda (a) (CountEven a (+ lvl 1))) tree)
;;             )
;;         ) 
;;     ) 
;; )

;(fn '(A (B 2) (2 C 4) (1 (3 F)) (((G) 4) 2)) 1)
(defun isLinear(l)
    (cond
        ((null l)
            t
        )
        ((listp (car l))
            NIL
        )
        (t
            (isLinear (cdr l))
        )
    )
)

(defun fn(_list lvl)
    (cond 
        ((atom _list)
            0
        )
        (
            (and
                (isLinear _list)
                (evenp (apply #'min _list))
                (not (evenp lvl))
            )
            1
        )
        (
            (and 
                (isLinear _list)
                (not (evenp (apply #'min _list)))
                (not (evenp lvl))
            )
            0
        )
        ((evenp lvl)
            0
        )
        (t
            (apply 
                #'+ 
                (mapcar
                    #'(lambda (p) 
                        (fn p (+ lvl 1))
                    )
                    _list
                )
            )
        )
    )
)
