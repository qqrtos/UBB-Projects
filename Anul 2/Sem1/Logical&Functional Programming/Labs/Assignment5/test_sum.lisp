(defun suma
    (l)
    (cond 
        ((null l) 0)
        (
            (numberp 
                (car l))
            (+
                (car l)
                (suma
                    (cdr l))
            )
        )
        (t
            (suma (cdr l))
        )
    )
)