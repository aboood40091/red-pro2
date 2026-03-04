import os

def count_lines_in_file(path: str) -> int:
    # Count text lines; skip files that can't be decoded as UTF-8.
    try:
        with open(path, "r", encoding="utf-8", errors="strict") as f:
            return sum(1 for _ in f)
    except (UnicodeDecodeError, OSError):
        return 0

def main() -> None:
    base = os.getcwd()
    script_path = os.path.normcase(os.path.abspath(__file__))
    total = 0
    scanned_files: list[str] = []

    for name in os.listdir(base):
        path = os.path.join(base, name)
        if os.path.isfile(path) and os.path.normcase(os.path.abspath(path)) != script_path:
            count = count_lines_in_file(path)
            if count == 0:
                continue
            scanned_files.append(name)
            total += count

    print(total)
    for name in scanned_files:
        print(name)

if __name__ == "__main__":
    main()
