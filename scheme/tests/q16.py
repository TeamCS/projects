test = {
  'names': [
    'q16',
    'Q16',
    '16'
  ],
  'points': 2,
  'suites': [
    [
      {
        'test': r"""
        >>> eval('''
        ... (let ((x 5))
        ...   (let ((x 2)
        ...         (y x))
        ...     (+ y (* x 2))))
        ... ''')
        9
        >>> eval("(let ((x 1) (y x)) y)")
        SchemeError
        # choice: SchemeError
        # choice: 1
        # choice: x
        # choice: y
        """,
        'type': 'doctest'
      },
      {
        'never_lock': True,
        'test': r"""
        >>> eval('''
        ... (define (square x) (* x x))
        ... (define (f x y)
        ...   (let ((a (+ 1 (* x y)))
        ...         (b (- 1 y)))
        ...     (+ (* x (square a))
        ...        (* y b)
        ...        (* a b))))
        ... (f 3 4)
        ... ''')
        456
        """,
        'type': 'doctest'
      }
    ],
    [
      {
        'never_lock': True,
        'test': r"""
        >>> eval('''
        ... (define x 3)
        ... (define y 4)
        ... (let ((x (+ y 2))
        ...       (y (+ x 1)))
        ...   (cons x y))
        ... ''')
        Pair(6, 4)
        >>> eval("(let ((x 'hello)) x)")
        'hello'
        >>> eval('''
        ... (let ((x 1)
        ...       (y 3))
        ...  (define x (+ x 1))
        ...  (cons x y))
        ... ''')
        Pair(2, 3)
        >>> eval("(let ((a 1 1)) a)")
        SchemeError
        >>> eval("(let ((a 1) (2 2)) a)")
        SchemeError
        """,
        'type': 'doctest'
      }
    ]
  ]
}