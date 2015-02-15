test = {
  'names': [
    'q07',
    'q7',
    'Q7',
    '7'
  ],
  'points': 2,
  'suites': [
    [
      {
        'test': r"""
        >>> eval("(begin (+ 2 3) (+ 5 6))")
        11
        >>> eval("(begin (define x 3) x)")
        3
        """,
        'type': 'doctest'
      }
    ],
    [
      {
        'test': r"""
        >>> eval("(begin 30 '(+ 2 2))")
        Pair('+', Pair(2, Pair(2, nil)))
        # choice: Pair('+', Pair(2, Pair(2, nil)))
        # choice: Pair('quote', Pair(Pair('+', Pair(2, Pair(2, nil))), nil))
        # choice: 4
        # choice: 30
        >>> eval('''
        ... (define x 0)
        ... (begin 42 (define x (+ x 1)))
        ... x
        ... ''')  # the last expression in do_begin_form should only be evaluated once
        1
        """,
        'type': 'doctest'
      },
      {
        'never_lock': True,
        'test': r"""
        >>> eval("(begin 30 'hello)")
        'hello'
        >>> eval("(begin (define x 3) (cons x '(y z)))")
        Pair(3, Pair('y', Pair('z', nil)))
        """,
        'type': 'doctest'
      }
    ]
  ]
}