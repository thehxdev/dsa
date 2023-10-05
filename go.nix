{ pkgs ? import <nixpkgs> {} }:
  pkgs.mkShell {
    # nativeBuildInputs is usually what you want -- tools you need to run
    nativeBuildInputs = with pkgs.buildPackages; [
        go
        gopls
        gdb
    ];

    #shellHook = ''
    #  export CGO_ENABLED=1
    #'';
}
