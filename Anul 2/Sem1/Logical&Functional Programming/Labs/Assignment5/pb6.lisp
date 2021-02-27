; INIT: (load "pb6.lisp")

; ------------------------------------------------------------------------------

; 6 a)
; isLinearList(l1..ln) = True, n=0
;                        False, l1 is list 
;                        isLinearList(l2..ln), otherwise
(defun isLinearList(l)
    (cond 
        ((null l) 
            T
        )
        ((listp (car l)) 
            NIL
        )
        (T 
            (isLinearList (cdr l))
        )
    )
)
; (isLinearList '(1 2 a 3 b)) --> T
; (isLinearList '(1 '(a 2) 3 '(4 '(g)))) --> NIL

; ------------------------------------------------------------------------------

; 6 b)
; replaceFirstOccurence(l1..ln, e, o) = [], n=0
;                                      o U replaceFirstOccurence(l2..ln, e, o), l1 = e
;                                      l1 U replaceFirstOccurence(l2..ln, e, o), otherwise
(defun replaceFirstOccurence(l elem other)
    (cond
        ((null l) 
            NIL
        )
        ;; ((listp (car l))
        ;;     (replaceFirstOccurence (car l) elem other)
        ;; )
        ((= (car l) elem) 
            (cons 
                other 
                (cdr l)
            )
        )
        (T
            (cons 
                (car l)
                (replaceFirstOccurence (cdr l) elem other)
            )
        )
    )
)
; (replaceFirstOccurence '(1 2 1 3 3) 1 0)

; ------------------------------------------------------------------------------

; 6 c)
; _reverse(l1..ln) = [], n = 0
;                    [l1] U reverse(l2..ln), otherwise
(defun _reverse(l)
    (cond 
        ((null l)
            NIL
        )
        (T
            (append 
                (_reverse (cdr l))
                (list (car l))
            )
        )
    )
)
; (_reverse '(1 2 '(3 4) 5 6))

; lastElement(l1..ln) = lastElement(k1), k1..kn = _reverse(l1..ln), l1..ln is list
;                       l1, otherwise
(defun lastElement(l)
    (cond 
        ((listp l)
            (lastElement 
                (car (_reverse l))
            )
        )
        (T
            l
        )
    )
)
; (lastElement '(1 '(2 '(3))))

; reduce(l1..ln) = [], n = 0
;                  lastElement(l1) U reduce(l2..ln), l1 is list
;                  l1 U reduce(l2..ln), otherwise
(defun _reduce(l)
    (cond 
        ((null l)
            NIL
        )
        ((listp (car l))
            (cons 
                (lastElement (car l))
                (_reduce (cdr l))
            )
        )
        (T
            (cons 
                (car l)
                (_reduce (cdr l))
            )
        )
    )
)
; (_reduce '(1 2 '(3 '(4 '(5)))))

; ------------------------------------------------------------------------------

; 6 d)
; mergeSorted(l1..ln, k1..km) = k1..km, n = 0
;                               l1..ln, m = 0, n > 0
;                               l1 U mergeSorted(l2..ln, k1..km), l1 < k1
;                               k2 U mergeSorted(l1..ln, k2..km), otherwise
(defun mergeSorted(l k)
    (cond
        ((null l) k)
        ((null k) l)
        ((< (car l) (car k))
            (cons
                (car l)
                (mergeSorted (cdr l) k)
            )
        )
        (T
            (cons
                (car k)
                (mergeSorted l (cdr k))
            )
        )
    )
)
; (mergeSorted '(1 1 2 3) '(2 4 5))

; removeNeighbouringDuplicates(l1..ln) = [l1], n = 1
;                           removeNeighbouringDuplicates(k..ln) , l = k
;                           l1 U removeNeighbouringDuplicates(k..ln), otherwise
(defun removeNeighbouringDuplicates(l)
    (cond
        ((null (cdr l))
            (list (car l))
        )
        ((= (car l) (cadr l))
            (removeNeighbouringDuplicates (cdr l))
        )
        (T
            (cons 
                (car l) 
                (removeNeighbouringDuplicates (cdr l))
            )
        )
    )
)
; (removeNeighbouringDuplicates '(1 1 2 3 3 4))

(defun mergeSortedNoDuplicates(l k)
    (removeNeighbouringDuplicates (mergeSorted l k))
)
; (mergeSortedNoDuplicates '(1 2 3 3 4) '(1 3 3 4 4 5 5)) 