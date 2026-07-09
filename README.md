# Bloom Filter implementation

Bloom filter is a space-efficient probabilistic data structure that is used to find if an element is in a set.

Bloom filter queries returns two possible answers:

1. Definitely NOT in the set
2. Probably in the set

Thus it never has false negatives but can have false positives.