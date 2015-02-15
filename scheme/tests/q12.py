test = {
  'names': [
    'q12',
    'Q12',
    '12'
  ],
  'points': 2,
  'suites': [
    [
      {
        'never_lock': True,
        'test': r"""
        >>> eval("(define (square x) (* x x)) (square 21)")
        441
        >>> eval("(define square (lambda (x) (* x x))) (square (square 21))")
        194481
        """,
        'type': 'doctest'
      },
      {
        'test': r"""
        >>> quine = "((lambda (x) (list x (list (quote quote) x))) (quote (lambda (x) (list x (list (quote quote) x)))))"
        >>> str(eval(quine)) == quine
        True
        """,
        'type': 'doctest'
      }
    ],
    [
      {
        'test': r"""
        >>> eval('''
        ... (define (outer x y)
        ...   (define (inner z x)
        ...     (+ x (* y 2) (* z 3)))
        ...   (inner x 10))
        ... (outer 1 2)
        ... ''')
        17
        >>> eval('''
        ... (define (outer-func x y)
        ...    (define (inner z x)
        ...      (+ x (* y 2) (* z 3)))
        ...    inner)
        ... ((outer-func 1 2)  1 10)
        ... ''')
        17
        """,
        'type': 'doctest'
      },
      {
        'never_lock': True,
        'test': r"""
        >>> eval('''
        ... (define square (lambda (x) (* x x)))
        ... (define (sum-of-squares x y)
        ...   (+ (square x) (square y)))
        ... (sum-of-squares 3 4)
        ... ''')
        25
        >>> eval('''
        ... (define double (lambda (x) (* 2 x)))
        ... (define compose (lambda (f g) (lambda (x) (f (g x)))))
        ... (define apply-twice (lambda (f) (compose f f)))
        ... ((apply-twice double) 5)
        ... ''')
        20
        """,
        'type': 'doctest'
      }
    ]
  ]
}