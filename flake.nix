{
    description = "Nix Flake-Based development environment for C";

    inputs = {
        nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";
    };

    outputs = { self, nixpkgs, ... }: let
        supportedSystems = [ "x86_64-linux" "aarch64-linux" "x86_64-darwin" "aarch64-darwin" ];

        forAllSystems = nixpkgs.lib.genAttrs supportedSystems;

        nixpkgsFor = forAllSystems (system: import nixpkgs { inherit system; });
    in {
        devShells = forAllSystems (system: let
            pkgs = nixpkgsFor.${system};
        in { 
            default = import ./shell.nix { inherit pkgs; };
        });
    };
}
