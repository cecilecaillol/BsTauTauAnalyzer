import os
import ROOT

def check_root_files(directory):
    invalid_files = []
    empty_tree_files = []
    valid_files = []

    for filename in os.listdir(directory):
        if not filename.endswith(".root"):
            continue

        path = os.path.join(directory, filename)
        f = ROOT.TFile.Open(path)
        if not f or f.IsZombie():
            invalid_files.append(filename)
            continue

        keys = f.GetListOfKeys()
        tree_found = False

        for key in keys:
            obj = key.ReadObj()
            if isinstance(obj, ROOT.TTree):
                tree_found = True
                break

        if not tree_found:
            empty_tree_files.append(filename)
        else:
            valid_files.append(filename)

        f.Close()

    print("\n=== ROOT File Check Summary ===")
    print(f"Directory: {directory}")
    print(f"Total ROOT files: {len(valid_files) + len(empty_tree_files) + len(invalid_files)}")
    print(f"#  Valid files with trees: {len(valid_files)}")
    print(f"## Files with NO trees: {len(empty_tree_files)}")
    print(f"#  Invalid or unreadable files: {len(invalid_files)}\n")

    if empty_tree_files:
        print("Files with no trees:")
        for f in empty_tree_files:
            print(f"rm {directory}/{f}")

    if invalid_files:
        print("\nInvalid/unreadable files:")
        for f in invalid_files:
            print(f"rm  {directory}/{f}")

if __name__ == "__main__":
    import sys
    if len(sys.argv) != 2:
        print("Usage: python check_root_files_pyroot.py <directory>")
        sys.exit(1)
    check_root_files(sys.argv[1])

