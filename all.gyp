{
    'targets':
    [
        {
            'target_name': 'all',
            'type': 'none',
            'dependencies':
            [
                'libs/m1/vector/gypfile:m1.vector',
                'libs/m1/vector/gypfile:m1.vector.test',
                'libs/r1/data_structure/gypfile:r1.data_structure',
                'libs/r1/data_structure/gypfile:r1.data_structure.test',
                'libs/r1/algorithm/gypfile:r1.algorithm',
                'libs/r1/algorithm/gypfile:r1.algorithm.test',
            ],
        },
    ],
}
