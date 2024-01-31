{
    description = "Nix Flake-Based development environment for C Language";

    inputs = {
        nixpkgs.url = "github:nixos/nixpkgs/nixos-23.11";
    };

    outputs = { self, nixpkgs, ... }: let
        system = "x86_64-linux";
    in {
        devShells."${system}".default = let
            pkgs = import nixpkgs { inherit system; };
        in pkgs.mkShell {
            packages = with pkgs; [
                # compiler and cmake
                clang_17
                llvmPackages_17.bintools
                gnumake
                cmake

                # debugging stuff
                gdb
                valgrind
            ];


            LIBCLANG_PATH = pkgs.lib.makeLibraryPath [ pkgs.llvmPackages_latest.libclang.lib ];
            BINDGEN_EXTRA_CLANG_ARGS = (builtins.map (a: ''-I"${a}/include"'') [
              # add dev libraries here (e.g. pkgs.libvmi.dev)
              pkgs.glibc.dev 
            ]) ++ [ # Includes with special directory paths
              ''-I"${pkgs.llvmPackages_latest.libclang.lib}/lib/clang/${pkgs.llvmPackages_latest.libclang.version}/include"''
              ''-I"${pkgs.glib.dev}/include/glib-2.0"''
              ''-I${pkgs.glib.out}/lib/glib-2.0/include/''
            ];

            # shellHook = ''
            # '';
        };
    };
}

