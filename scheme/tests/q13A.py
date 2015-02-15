test = {
  'names': [
    'q13A',
    'Q13A',
    'qA13',
    'QA13',
    'A13',
    '13A',
    '13'
  ],
  'points': 1,
  'suites': [
    [
      {
        'test': r"""
        >>> eval("(if #t 1 0)")
        1
        >>> eval("(if #f 1 0)")
        0
        >>> eval("(if 1 1 0)")
        1
        >>> eval("(if 0 1 0)")
        1
        >>> eval("(if 'a 1 0)")
        1
        >>> eval("(if (cons 1 2) 1 0)")
        1
        >>> eval("(if #t 1)")
        1
        >>> eval("(if #f 1)")
        okay
        >>> eval("(if #t '(1))")
        Pair(1, nil)
        """,
        'type': 'doctest'
      }
    ]
  ]
}