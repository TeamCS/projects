test = {
  'names': [
    'q02',
    'q2',
    'Q2',
    '2'
  ],
  'points': 2,
  'suites': [
    [
      {
        'test': r"""
        >>> read_line("(a . b)")
        Pair('a', 'b')
        # choice: Pair('a', Pair('b'))
        # choice: Pair('a', Pair('b', nil))
        # choice: SyntaxError
        # choice: Pair('a', 'b')
        # choice: Pair('a', 'b', nil)
        >>> read_line("(a b . c)")
        Pair('a', Pair('b', 'c'))
        # choice: Pair('a', Pair('b', Pair('c', nil)))
        # choice: Pair('a', Pair('b', Pair('c')))
        # choice: Pair('a', 'b', 'c')
        # choice: Pair('a', Pair('b', 'c'))
        # choice: SyntaxError
        """,
        'type': 'doctest'
      }
    ],
    [
      {
        'test': r"""
        >>> read_line("(a b . c d)")
        SyntaxError
        # choice: Pair('a', Pair('b', Pair('c', 'd')))
        # choice: Pair('a', Pair('b', 'c'))
        # choice: Pair('a', Pair('b', Pair('c', Pair('d', nil))))
        # choice: SyntaxError
        >>> read_line("(a . (b . (c . ())))")
        Pair('a', Pair('b', Pair('c', nil)))
        # choice: Pair('a', Pair('b', Pair('c', nil)))
        # choice: SyntaxError
        # choice: Pair('a', Pair('b', Pair('c', Pair(nil, nil))))
        # choice: Pair('a', 'b', 'c')
        >>> read_line("(a . ((b . (c)))))")
        Pair('a', Pair(Pair('b', Pair('c', nil)), nil))
        # choice: Pair('a', Pair(Pair('b', Pair('c', nil)), nil))
        # choice: Pair('a', Pair('b', Pair('c', nil)), nil)
        # choice: Pair('a', Pair('b', Pair('c')), nil)
        # choice: Pair('a', Pair(Pair('b', Pair('c', nil)), nil), nil)
        """,
        'type': 'doctest'
      },
      {
        'never_lock': True,
        'test': r"""
        >>> read_line("(. . 2)")
        SyntaxError
        >>> read_line("(2 . 3 4 . 5)")
        SyntaxError
        >>> read_line("(2 (3 . 4) 5)")
        Pair(2, Pair(Pair(3, 4), Pair(5, nil)))
        >>> read_line("(1 2")
        SyntaxError
        """,
        'type': 'doctest'
      }
    ]
  ]
}