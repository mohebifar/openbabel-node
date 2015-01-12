{
  "targets": [
    {
      "target_name": "openbabel",
      "sources": [
        "src/atom.cpp",
        "src/data.cpp",
        "src/mol.cpp",
        "src/bond.cpp",
        "src/addon.cpp",
        "src/forcefield.cpp",
        "src/builder.cpp",
        "src/conversion.cpp"
      ],
      "defines": [
        "GCC_ENABLE_CPP_RTTI = YES"
      ],
      "include_dirs": ["<!(node -e \"require('nan')\")", "/usr/local/lib/openbabel/2.3.2", "/usr/local/include/openbabel-2.0", "/usr/include/openbabel-2.0", "/usr/local/include/openbabel-2.0/openbabel"],
      "conditions": [
        ["OS=='win'", {

        }],
        ["OS=='win' and target_arch!='x64'", {

        }],
        ["OS=='mac'", {
          "libraries": [
            "-lopenbabel"
          ],
          "cflags": [
            "-pipe"
          ],
          "cflags_cc!": [ "-fno-rtti" ]
        }],
        ["OS=='linux'", {
          "libraries": [
            "-lopenbabel"
          ],
          "cflags": [
            "-pipe"
          ],
          "cflags_cc!": [ "-fno-rtti" ]
        }]
      ]
    }
  ]
}
