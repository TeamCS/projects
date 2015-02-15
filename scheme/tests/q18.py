test = {
  'names': [
    'q18',
    'Q18',
    '18'
  ],
  'points': 1,
  'suites': [
    [
      {
        'never_lock': True,
        'test': r"""
        >>> check_scheme("(zip '())")
        '(() ())'
        >>> check_scheme("(zip '((1 2)))")
        '((1) (2))'
        >>> check_scheme("(zip '((1 2) (3 4) (5 6)))")
        '((1 3 5) (2 4 6))'
        """,
        'type': 'doctest'
      }
    ]
  ]
}