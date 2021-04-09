1.
a. (let ((class ( ref 342))) (let ((course class)) (deref course)))
    342

b. (define pairNode (lambda (fst snd) (lambda (op) (if op fst snd))))
   (define node (lambda (x) (pairNode x (ref (list)))))
   (define getFst (lambda (p) (p #t)))
   (define getSnd (lambda (p) (p #f)))
   i.
   A. (define treeNode (lambda (fst snd) (lambda (op) (if op fst snd))))
   B. (define node (lambda (x) (treeNode x (ref (list)))))
   C. (define getFst (lambda (p) (p #t)))
      (define getSnd (lambda (p) (p #f)))
      (define value (lambda (x) ()
