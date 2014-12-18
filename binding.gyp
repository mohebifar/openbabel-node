{
  "targets": [
    {
      "target_name": "openbabel",
      "sources": [
        "src/addon.cpp",
        "src/conversion.cpp",
        "src/atom.cpp",
        "src/mol.cpp"
      ],
      "include_dirs": ["<!(node -e \"require('nan')\")"],
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
