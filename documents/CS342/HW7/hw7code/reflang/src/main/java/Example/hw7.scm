1.
a. (let ((class ( ref 342))) (let ((course class)) (deref course)))
    342
b.
   i.
   A. (define treeNode (lambda (fst snd) (lambda (op) (if op fst snd))))
   B. (define node (lambda (x) (treeNode x (treeNode (ref (list)) (ref (list))))))
   C. (define value (lambda (p) (p #t)))
   D. (define left (lambda (p) ((p #f) #t)))
      (define right (lambda (p) ((p #f) #f)))
   ii. (define add (lambda (p op c) (if op (set! (left p) c) (set! (right p) c))))
