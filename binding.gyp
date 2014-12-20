{
  "targets": [
    {
      "target_name": "openbabel",
      "sources": [
        "src/forcefield.cpp",
        "src/conversion.cpp",
        "src/atom.cpp",
        "src/mol.cpp",
        "src/addon.cpp"
      ],
      "libraries": [
        "-lopenbabel"
      ],
      "include_dirs": ["<!(node -e \"require('nan')\")", "/usr/local/lib/openbabel/2.3.2", "/usr/local/include/openbabel-2.0"],
      "conditions": [
        ['OS=="win"', {

        }],
        ['OS=="win" and target_arch!="x64"', {

        }],
        ['OS=="mac"', {

        }],
        ['OS=="linux"', {
          "libraries": [
            "-lopenbabel"
          ],
          "cflags": [
            "-pipe"
          ]
        }]
      ]
    }
  ]
}
