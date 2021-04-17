
6.
    (deref 45) // test incorrect reference type for dereference expressions
    (set! (ref : bool #t) (list : num 1 2 3 4 5 6 )) // test incorrect num type for set expressions
    (car 2) // test incorrect pair/list type for car expressions
    (list : bool 1 2 3 4 5 6 7) // test incorrect bool type for list expressions
    (define add: (num num num -> num) (lambda ( x: num y: num z: num) (+ x (+ y z))))
    (add 5 56 #t) // test incorrect type for add
    (3 4) // test incorrect function type
    (> 3 #t) // test incorrect type for comparator expressions
    (if 2 1 0) // test incorrect bool type for if expressions

7.
   (define pair: (num num -> list) (lambda (fst: num snd: num) ( (op: num) (if (= op 0) (if (= fst snd) (list fst snd) (if (= op 1) (if (= fst snd) (list -1 -1)) (list -1 -1)))))
   (define common: (T) (lambda (T: list) (p 0)))
   (define diff: (T) (lambda (T: list) (p 1)))
   (define processlists: (T list list -> list) (lambda (op:T lst1:list lst2:list) (if (null? (cdr lst1)) (list (cons (op (pair (car (car lst1)) (car (car lst2)))) (op (pair (cdr (car lst1)) (cdr (car lst2)))))) (cons (cons (op (pair (car (car lst1)) (car (car lst2)))) (op (pair (cdr (car lst1)) (cdr (car lst2))))) (processlists op (cdr lst1) (cdr lst2))))))