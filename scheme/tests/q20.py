test = {
  'names': [
    'q20',
    'Q20',
    '20'
  ],
  'points': 2,
  'suites': [
    [
      {
        'never_lock': True,
        'test': r"""
        >>> check_scheme("(analyze 1)")
        '1'
        >>> check_scheme("(analyze 'a)")
        'a'
        >>> check_scheme("(analyze '(+ 1 2))")
        '(+ 1 2)'
        >>> check_scheme("(analyze '(quote (let ((a 1) (b 2)) (+ a b))))")
        '(quote (let ((a 1) (b 2)) (+ a b)))'
        """,
        'type': 'doctest'
      }
    ],
    [
      {
        'never_lock': True,
        'test': r"""
        >>> check_scheme("(analyze '(lambda (let a b) (+ let a b)))")
        '(lambda (let a b) (+ let a b))'
        >>> check_scheme("(analyze '(lambda (x) a (let ((a x)) a)))")
        '(lambda (x) a ((lambda (a) a) x))'
        """,
        'type': 'doctest'
      },
      {
        'never_lock': True,
        'test': r"""
        >>> check_scheme('''
        ... (analyze '(let ((a 1)
        ...                 (b 2))
        ...             (+ a b)))
        ... ''')
        '((lambda (a b) (+ a b)) 1 2)'
        >>> check_scheme('''
        ... (analyze '(let ((a (let ((a 2)) a))
        ...                 (b 2))
        ...             (+ a b)))
        ... ''')
        '((lambda (a b) (+ a b)) ((lambda (a) a) 2) 2)'
        >>> check_scheme('''
        ... (analyze '(let ((a 1))
        ...             (let ((b a))
        ...               b)))
        ... ''')
        '((lambda (a) ((lambda (b) b) a)) 1)'
        >>> check_scheme("(analyze '(+ 1 (let ((a 1)) a)))")
        '(+ 1 ((lambda (a) a) 1))'
        """,
        'type': 'doctest'
      }
    ]
  ]
}