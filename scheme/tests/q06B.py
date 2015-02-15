test = {
  'names': [
    'q06B',
    'q6B',
    'Q6B',
    'qB6',
    'QB6',
    'B6',
    '6B',
    '6'
  ],
  'points': 1,
  'suites': [
    [
      {
        'answer': 'Pair(A, nil), where: A is the quoted expression',
        'choices': [
          r"""
          Pair('quote', Pair(A, nil)), where:
            A is the quoted expression
          """,
          r"""
          [A], where:
            A is the quoted expression
          """,
          r"""
          Pair(A, nil), where:
            A is the quoted expression
          """
        ],
        'question': 'What does the parameter vals look like?',
        'type': 'concept'
      },
      {
        'test': r"""
        >>> eval("(quote 3)")
        3
        # choice: Pair('quote', Pair(3, nil))
        # choice: Pair(3, nil)
        # choice: 3
        >>> eval("(quote (1 2))")
        Pair(1, Pair(2, nil))
        # choice: Pair('quote', Pair(1, Pair(2, nil)))
        # choice: Pair(1, 2)
        # choice: Pair(1, Pair(2, nil))
        # choice: SchemeError
        >>> eval("(car '(1 2 3))")
        1
        >>> eval("(car (car '((1))))")
        1
        >>> eval("'hello")
        'hello'
        # choice: Pair('quote', Pair('hello', nil))
        # choice: Pair('hello', nil)
        # choice: 'hello'
        >>> eval("''hello")
        Pair('quote', Pair('hello', nil))
        # choice: Pair('quote', Pair('quote', Pair('hello', nil)))
        # choice: Pair('quote', Pair('hello', nil))
        # choice: Pair('hello', nil)
        # choice: 'hello'
        """,
        'type': 'doctest'
      }
    ]
  ]
}