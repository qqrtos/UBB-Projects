;; (defun f1(l)
;;     (cond 
;;         ((null l)
;;             NIL
;;         )
;;         ((listp (car l))
;;             (append 
;;                 (f1 (car l))
;;                 (f1 (cdr l))
;;                 (car (f1 (car l)))
;;             )
;;         )
;;     )
;; )

;; (defun f2(l)
;;     (cond 
;;         ((null l)
;;             NIL
;;         )
;;         ((listp (car l))
;;             ;; (append 
;;             ;;     (f2 (car l))
;;             ;;     (f2 (cdr l))
;;             ;;     (car (f2 (car l)))
;;             ;; )
;;             (
;;                 (lambda (v)
;;                     (append
;;                         v
;;                         (f2 (cdr l))
;;                         (car v)
;;                     )
;;                 )
;;                 (f2 (car l))
;;             )
;;         )
;;     )
;; )

;; (defun g1(l)
;;     (cond
;;         ((null l) 
;;             nil
;;         )
;;         (t 
;;             (cons 
;;                 (car (f l))
;;                 (cadr (f l))
;;             )
;;         )
;;     )
;; )

;; (defun g2(l)
;;     (cond
;;         ((null l) 
;;             nil
;;         )
;;         (t 
;;             (
;;                 (lambda (v) 
;;                     (cons 
;;                         (car v)
;;                         (cadr v)
;;                     )
;;                 )
;;                 (f l)
;;             )
;;         )
;;     )
;; )
