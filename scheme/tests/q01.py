test = {
  'names': [
    'q01',
    'q1',
    'Q1',
    '1'
  ],
  'points': 1,
  'suites': [
    [
      {
        'never_lock': True,
        'test': r"""
        >>> read_line('3')
        3
        >>> read_line('-123')
        -123
        >>> read_line('1.25')
        1.25
        >>> read_line('true')
        True
        >>> read_line('(a)')
        Pair('a', nil)
        >>> read_line(')')
        SyntaxError
        """,
        'type': 'doctest'
      },
      {
        'test': r"""
        >>> read_line("'x")
        Pair('quote', Pair('x', nil))
        # choice: Pair('x', nil)
        # choice: 'x'
        # choice: Pair('quote', 'x')
        # choice: Pair('quote', Pair('x', nil))
        >>> read_line("(quote x)")
        Pair('quote', Pair('x', nil))
        # choice: Pair('quote', 'x')
        # choice: Pair('x', nil)
        # choice: 'x'
        # choice: Pair('quote', Pair('x', nil))
        >>> read_line("'(a b)")
        Pair('quote', Pair(Pair('a', Pair('b', nil)), nil))
        # choice: Pair('a', Pair('b', nil))
        # choice: Pair('quote', Pair(Pair('a', Pair('b', nil)), nil))
        # choice: Pair('quote', Pair('a', 'b'))
        # choice: Pair('quote', Pair('a', Pair('b', nil)))
        >>> read_line("'((a))")
        Pair('quote', Pair(Pair(Pair('a', nil), nil), nil))
        # choice: Pair('quote', Pair(Pair('a', nil), nil))
        # choice: Pair('quote', Pair(Pair('a', nil), nil), nil)
        # choice: Pair('quote', Pair(Pair('a'), nil))
        # choice: Pair('quote', Pair(Pair('a'), nil), nil)
        # choice: Pair('quote', Pair(Pair(Pair('a', nil), nil), nil))
        """,
        'type': 'doctest'
      },
      {
        'never_lock': True,
        'test': r"""
        >>> read_line("(a (b 'c))")
        Pair('a', Pair(Pair('b', Pair(Pair('quote', Pair('c', nil)), nil)), nil))
        >>> read_line("(a (b '(c d)))")
        Pair('a', Pair(Pair('b', Pair(Pair('quote', Pair(Pair('c', Pair('d', nil)), nil)), nil)), nil))
        >>> read_line("')")
        SyntaxError
        """,
        'type': 'doctest'
      }
    ]
  ]
}