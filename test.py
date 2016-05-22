#!/usr/bin/env python
# Tests adapted from: https://github.com/MostAwesomeDude/java-random

import unittest

from java_random import JavaRandom

class AccuracyTest(unittest.TestCase):

    def setUp(self):
        self.r = JavaRandom(0)

    """def test_nextBytes(self):
        standard = [96, -76, 32, -69, 56, 81, -39, -44]
        l = [None] * len(standard)
        self.r.nextBytes(l)
        self.assertEqual(l, standard)"""

    """def test_nextInt(self):
        standard = -1155484576
        self.assertEqual(self.r.nextInt(), standard)"""

    """def test_nextInt_lue(self):
        standard = 12
        self.assertEqual(self.r.nextInt(42), standard)"""

    """def test_nextLong(self):
        standard = -4962768465676381896
        self.assertEqual(self.r.nextLong(), standard)"""

    """def test_nextBoolean(self):
        standard = True
        self.assertEqual(self.r.nextBoolean(), standard)"""

    """def test_nextFloat(self):
        standard = 0.73096776008605960
        self.assertEqual(self.r.nextFloat(), standard)"""

    def test_nextDouble(self):
        standard = 0.73096778737665700
        self.assertEqual(self.r.nextDouble(), standard)

    def test_nextGaussian(self):
        standard = (0.80253306373903050, -0.90154608841751220)
        self.assertEqual((self.r.nextGaussian(), self.r.nextGaussian()), standard)

if __name__ == "__main__":
    unittest.main()
