#!/usr/bin/env bash

INPUT_FILES="./inputs"
TARGET="./target"
JAR_FILE="./target/java-aoc-1.0-SNAPSHOT.jar"

if [[ $# -ne 2 ]]; then
    echo "Usage: bash run.sh <Year> <Day>" ; exit 1
fi

function log() {
    echo "[$1] $2"
}

if ! command -v java >/dev/null; then
    log "ERROR" "Cannot find java executable in your PATH."
    log "INFO" "Please install JDK."
fi

if ! command -v mvn >/dev/null; then
    log "ERROR" "Cannot find mvn (Maven) executable in your PATH."
    log "INFO" "Please install Maven from https://maven.apache.org"
    exit 1
fi

if [[ ! -e "$TARGET" ]]; then
    mvn package || exit 1
    sleep 2
    clear
fi

java -cp "$JAR_FILE" "aoc$1.d$2.Main" "$INPUT_FILES/$1-d$2"
