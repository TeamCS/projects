test = {
  'names': [
    'q14B',
    'Q14B',
    'qB14',
    'QB14',
    'B14',
    '14B',
    '14'
  ],
  'points': 2,
  'suites': [
    [
      {
        'test': r"""
        >>> eval("(and)")
        True
        # choice: True
        # choice: False
        # choice: SchemeError
        >>> eval("(and 1 #f)")
        False
        # choice: 1
        # choice: True
        # choice: False
        >>> eval("(and 2 1)")
        1
        # choice: 2
        # choice: 1
        # choice: True
        # choice: False
        >>> eval("(and #f 5)")
        False
        # choice: 5
        # choice: True
        # choice: False
        >>> eval('''
        ... (define x 0)
        ... (and 3 (define x (+ x 1)))
        ... x
        ... ''')
        1
        >>> eval('''
        ... (define x 0)
        ... (and (begin (define x (+ x 1)) #f) 3)
        ... x
        ... ''')
        1
        """,
        'type': 'doctest'
      },
      {
        'never_lock': True,
        'test': r"""
        >>> eval("(and 3 2 #f)")
        False
        >>> eval("(and 3 2 1)")
        1
        >>> eval("(and 3 #f 5)")
        False
        """,
        'type': 'doctest'
      }
    ],
    [
      {
        'test': r"""
        >>> eval("(or)")
        False
        # choice: True
        # choice: False
        # choice: SchemeError
        >>> eval("(or 1)")
        1
        # choice: 1
        # choice: True
        # choice: False
        # choice: SchemeError
        >>> eval("(or #f)")
        False
        # choice: True
        # choice: False
        # choice: SchemeError
        >>> eval("(or 0 1 2 'a)")
        0
        >>> eval('''
        ... (define x 0)
        ... (or (define x (+ x 1)) 3)
        ... x
        ... ''')
        1
        >>> eval('''
        ... (define x 0)
        ... (or #f (define x (+ x 1)))
        ... x
        ... ''')
        1
        """,
        'type': 'doctest'
      },
      {
        'never_lock': True,
        'test': r"""
        >>> eval("(or #f #f)")
        False
        >>> eval("(or 'a #f)")
        'a'
        >>> eval("(or (< 2 3) (> 2 3) 2 'a)")
        True
        >>> eval("(or (< 2 3) 2)")
        True
        """,
        'type': 'doctest'
      }
    ]
  ]
}