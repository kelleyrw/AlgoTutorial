{
    'target_defaults':
    {
        'msvs_settings':
        {
            'VCCLCompilerTool':
            {
                'WarningLevel': 4, # 'Level4'
                'WarnAsError': 'true',
                'DisableSpecificWarnings':
                [
                    '4351', # new behavior: elements of array will be default initialized
                    '4512', # assignment operator was implicitly defined as deleted
                    '4510', # default constructor was implicitly defined as deleted
                ],
            },
            'VCLinkerTool':
            {
                # Set /SUBSYSTEM:CONSOLE
                'SubSystem': '1',
            },
        },
        'configurations':
        {
            'Debug':
            {
                'msvs_configuration_platform': 'Win32',
                'msvs_settings':
                {
                    'VCCLCompilerTool':
                    {
                        'Optimization': 0, # 'Disabled'
                    },
                    'VCLinkerTool':
                    {
                        'GenerateDebugInformation': 'true',
                    },
                },
            },
            'Debug_x64':
            {
                'inherit_from':
                [
                    'Debug'
                ],
                'msvs_configuration_platform': 'x64',
            },
            'Release':
            {
                'msvs_configuration_platform': 'Win32',
                'defines':
                [
                    'NDEBUG',
                ],
                'msvs_settings':
                {
                    'VCCLCompilerTool':
                    {
                        'Optimization': 3, # 'Full'
                    },
                },
            },
            'Release_x64':
            {
                'inherit_from':
                [
                    'Release'
                ],
                'msvs_configuration_platform': 'x64',
            },
        },
        'default_configuration': 'Debug',
    },
}
