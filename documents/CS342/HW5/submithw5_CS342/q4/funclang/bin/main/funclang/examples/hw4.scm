// Q1
(define X 88)
(define Y 89)
(define Z 90)
(define x (+ X 32))
(define y (+ Y 32))
(define z (+ Z 32))

// Q2
(define f
	(lambda (n)
		(if (= n 1)
			1
			(if (= n 2)
				1
				(+ (f (- n 1)) (f (- n 2)) )
			)
		)
	)
)

// Q3(a)
(define count
	(lambda (n lst)
		(if (null? lst)
			0
			(if (= (car lst) n)
				( + 1 (count n (cdr lst)) )
				(count n (cdr lst))
			)
		)
	)
)

// Q3(b)
(define max
	(lambda (lst)
		(if (null? lst)
			0
			(maxhelper lst (car lst) )
		)
	)
)

(define maxhelper
	(lambda (lst max)
		(if (null? lst)
			max
			(if (> (car lst) max)
				(maxhelper (cdr lst) (car lst))
				(maxhelper (cdr lst) max )
			)
		)
	)
)

// Q3(c)
(define maxrepeat
	(lambda (lst)
		(if (null? lst)
			0
			(maxrepeathelper lst 1)
		)
	)
)

(define maxrepeathelper
	(lambda (lst max)
		(if (null? lst)
			max
			(if (> (count (car lst) lst) max)
				(maxrepeathelper (cdr lst) (count (car lst) lst))
				(maxrepeathelper (cdr lst) max)
			)
		)
	)
)

//(maxrepeat (list 11 11 31 14))

// Q4(a)
(define pairs (list (cons 1 5) (cons 6 4) (cons 7 8) (cons 15 10)))

// Q4(b)
(define secondSum
	(lambda (lst)
	    (+ (cdr (car pairs)) (cdr (car (cdr pairs))) (cdr (car (cdr (cdr pairs)))) (cdr (car (cdr (cdr (cdr pairs))))))
	)
)

// (secondSum pairs)

// Q5 (a)

(define pair (lambda (fst snd)  (lambda (op) (if op fst snd))))
(define apair (pair 2 3))

(define second
	(lambda (p) (p #f)
	)
)

// (second apair)

// Q5(b)
(define pair
	(lambda (fst snd)
		(lambda (op)
			(if (= op 0) (+ fst snd)
				(if (= op 1) (- fst snd)
					(if (= op 2) (* fst snd)
						(if (= op 3) (/ fst snd) 0
						)
					)
				)
			)
		)
	)
)

(define apair (pair 2 3))

// Q5(c)
(define add
	(lambda (p) (p 0)
	)
)

// (add apair)

// Q6(a)
(define mylist (list (cons 1 3) (cons 4 2) (cons 5 6)))
(define mult (lambda (x y) (* x y)))

// Q6(b)
(define applyonnth
	(lambda (op lst n)
		(if (null? lst)
			-1
			(if (= n 1)
				(op (car (car lst)) (cdr (car lst)))
				(if (< n 0)
					-1
					(applyonnth op (cdr lst) (- n 1))
				)
			)
		)
	)
)

// Q6(c)

//(define applyonnth
//	(lambda (op)
//		(lambda (lst)
//			(lambda (n)
//				(if (null? lst)
//					-1
//					(if (= n 1)
//						(op (car (car lst)) (cdr (car lst)))
//						(if (< n 0)
//							-1
//							(((applyonnth op) (cdr lst)) (- n 1)))
//						)
//				)
//			)
//		)
//	)
//)
