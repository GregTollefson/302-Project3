// driver.cpp
// CS 302 – Project 3: Music Library (Binary Search Tree)
//
// This driver demonstrates all required functionality of the
// MusicLibrary BST, matching the correctness checklist in project_03.md.
//
// HOW TO USE THIS FILE:
//   1. Search for every TODO comment and complete it.
//   2. Choose at least 8 songs. Sketch the resulting BST on paper.
//      Know which nodes are leaves, which have one child, which have two.
//   3. Do not remove any labeled sections — all checklist items must stay covered.
//
// REMINDER: Traversal methods require a visit function (see displaySong below).
// Lookup and removal take a Song object — use Song("Title", "", 0) to search by title only.

#include "Song.h"
#include "MusicLibrary.h"
#include "BinaryTreeInterface.h"
#include "NotFoundException.h"
#include <iostream>
#include <string>

using namespace std;

// --------------------------------------------------
// Visit function passed to all three traversal methods.
// Called once per node in traversal order.
// Uses Song::operator<< to display each song.
// --------------------------------------------------
void displaySong(Song& song)
{
    cout << "  " << song << endl;  // calls Song::display() via SongInterface::operator<<
}

// Prints a labeled section divider for readable output
void printSection(const string& label)
{
    cout << endl;
    cout << "========================================" << endl;
    cout << "  " << label << endl;
    cout << "========================================" << endl;
}

int main()
{
    MusicLibrary library;

    // --------------------------------------------------
    // CHECK: isEmpty() on empty library
    // --------------------------------------------------
    printSection("1. Empty Library Check");
    cout << "isEmpty():          " << (library.isEmpty() ? "true" : "false") << endl;
    cout << "getNumberOfNodes(): " << library.getNumberOfNodes() << endl;
    cout << "getHeight():        " << library.getHeight() << endl;

    // --------------------------------------------------
    // CHECK: Add at least 8 songs
    // --------------------------------------------------
    printSection("2. Adding Songs (at least 8)");

    // TODO: Add at least 8 songs of your choice using library.add().
    //
    // IMPORTANT — choose your insertion order carefully:
    //   - The order you call add() determines the shape of the BST.
    //   - Inserting in alphabetical order produces a degenerate (linear) tree.
    //   - Insert in a deliberate order so the tree stays balanced.
    //   - Aim for a tree where isBalanced() returns true (see section 3 below).
    //
    // ALSO — make sure your 8+ songs include:
    //   - At least one LEAF node (for removal test in section 9)
    //   - At least one node with exactly ONE CHILD (section 10)
    //   - At least one node with TWO CHILDREN (section 11)
    //   Sketch the tree on paper before coding the removal sections.
    //
    // Example:
    //   library.add(Song("Midnights",      "Taylor Swift", 2022));
    //   library.add(Song("Blinding Lights", "The Weeknd",  2019));
    
    library.add(Song("Karn Evil 9", "Emerson, Lake & Palmer", 1973));
    library.add(Song("Close to the Edge", "Yes", 1972));
    library.add(Song("Aqualung", "Jethro Tull", 1971));
    library.add(Song("Firth of Fifth", "Genesis", 1973));
    library.add(Song("Shine On You Crazy Diamond", "Pink Floyd", 1975));
    library.add(Song("Roundabout", "Yes", 1971));
    library.add(Song("Supper's Ready", "Genesis", 1972));
    library.add(Song("Time", "Pink Floyd", 1973));


    cout << "Songs added." << endl;
    cout << "getNumberOfNodes(): " << library.getNumberOfNodes() << endl;

    // --------------------------------------------------
    // CHECK: Display using all three traversals
    // CHECK: Inorder must produce alphabetical order by title
    // --------------------------------------------------
    printSection("3. Inorder Traversal (alphabetical by title)");
    library.inorderTraverse(displaySong);

    printSection("4. Preorder Traversal (Root → Left → Right)");
    library.preorderTraverse(displaySong);

    printSection("5. Postorder Traversal (Left → Right → Root)");
    library.postorderTraverse(displaySong);

    // --------------------------------------------------
    // CHECK: isBalanced(), getHeight(), getNumberOfNodes()
    // --------------------------------------------------
    printSection("6. Balance Check");
    cout << "getNumberOfNodes(): " << library.getNumberOfNodes() << endl;
    cout << "getHeight():        " << library.getHeight() << endl;
    cout << "isBalanced():       " << (library.isBalanced() ? "true" : "false") << endl;
    cout << endl;
    cout << "For a balanced tree of n nodes, expected height = floor(log2(n)) + 1" << endl;

    // --------------------------------------------------
    // CHECK: contains() — song that EXISTS
    // --------------------------------------------------
    printSection("7. Search — Song That Exists");
    // TODO: Replace "YOUR_SONG_TITLE" with a title you added above.
    Song existingSong("Roundabout", "Yes", 1971);
    cout << "Searching for \"" << existingSong.getTitle() << "\"..." << endl;
    cout << "contains(): " << (library.contains(existingSong) ? "true" : "false") << endl;

    // --------------------------------------------------
    // CHECK: contains() — song that DOES NOT EXIST
    // --------------------------------------------------
    printSection("8. Search — Song That Does Not Exist");
    // TODO: Use a title that is NOT in your library.
    Song missingSong("Brown Sugar", "Rolling Stones", 1971);
    cout << "Searching for \"" << missingSong.getTitle() << "\"..." << endl;
    cout << "contains(): " << (library.contains(missingSong) ? "true" : "false") << endl;

    // --------------------------------------------------
    // CHECK: getEntry() — song that EXISTS
    // --------------------------------------------------
    printSection("9. getEntry() — Song That Exists");
    // TODO: Replace "YOUR_SONG_TITLE" with a title you added above.
    try
    {
        Song query("Roundabout", "Yes", 1971);
        Song found = library.getEntry(query);
        cout << "getEntry() found: " << found << endl;
    }
    catch (const NotFoundException& e)
    {
        cout << "NotFoundException caught: " << e.what() << endl;
    }

    // --------------------------------------------------
    // CHECK: getEntry() — song that DOES NOT EXIST (NotFoundException)
    // --------------------------------------------------
    printSection("10. getEntry() — Song That Does Not Exist");
    // TODO: Use a title that is NOT in your library.
    try
    {
        Song badQuery("Brown Sugar", "Rolling Stones", 1971);
        Song found = library.getEntry(badQuery);
        cout << "getEntry() found: " << found << endl;  // should not reach here
    }
    catch (const NotFoundException& e)
    {
        cout << "NotFoundException caught (expected): " << e.what() << endl;
    }

    // --------------------------------------------------
    // CHECK: Remove a LEAF node
    // --------------------------------------------------
    printSection("11. Remove — Leaf Node");
    // TODO: Replace "LEAF_TITLE" with a title that is a LEAF in your BST.
    //       Verify by checking your paper sketch.
    Song leafSong("Time", "Pink Floyd", 1973);
    cout << "Removing \"" << leafSong.getTitle() << "\" (leaf)..." << endl;
    cout << "remove() returned: " << (library.remove(leafSong) ? "true" : "false") << endl;
    cout << "contains() after:  " << (library.contains(leafSong) ? "true" : "false") << endl;
    cout << "getNumberOfNodes(): " << library.getNumberOfNodes() << endl;
    cout << endl << "Inorder after removal:" << endl;
    library.inorderTraverse(displaySong);

    // --------------------------------------------------
    // CHECK: Remove a node with ONE CHILD
    // --------------------------------------------------
    printSection("12. Remove — Node With One Child");
    // TODO: Replace "ONE_CHILD_TITLE" with a title whose node has exactly one child.
    Song oneChildSong("Supper's Ready", "Genesis", 1972);
    cout << "Removing \"" << oneChildSong.getTitle() << "\" (one child)..." << endl;
    cout << "remove() returned: " << (library.remove(oneChildSong) ? "true" : "false") << endl;
    cout << "contains() after:  " << (library.contains(oneChildSong) ? "true" : "false") << endl;
    cout << "getNumberOfNodes(): " << library.getNumberOfNodes() << endl;
    cout << endl << "Inorder after removal:" << endl;
    library.inorderTraverse(displaySong);

    // --------------------------------------------------
    // CHECK: Remove a node with TWO CHILDREN
    // --------------------------------------------------
    printSection("13. Remove — Node With Two Children");
    // TODO: Replace "TWO_CHILDREN_TITLE" with a title whose node has two children.
    //       The inorder successor should replace it — verify in your output.
    Song twoChildSong("Close to the Edge", "Yes", 1972);
    cout << "Removing \"" << twoChildSong.getTitle() << "\" (two children)..." << endl;
    cout << "remove() returned: " << (library.remove(twoChildSong) ? "true" : "false") << endl;
    cout << "contains() after:  " << (library.contains(twoChildSong) ? "true" : "false") << endl;
    cout << "getNumberOfNodes(): " << library.getNumberOfNodes() << endl;
    cout << endl << "Inorder after removal:" << endl;
    library.inorderTraverse(displaySong);

    // --------------------------------------------------
    // CHECK: remove() on a title that DOES NOT EXIST
    // --------------------------------------------------
    printSection("14. Remove — Non-Existent Song (safe handling)");
    Song notExist("Brown Sugar", "Rolling Stones", 1971);
    cout << "Removing \"" << notExist.getTitle() << "\" (not in library)..." << endl;
    cout << "remove() returned: " << (library.remove(notExist) ? "true" : "false") << endl;
    cout << "getNumberOfNodes(): " << library.getNumberOfNodes() << endl;

    // --------------------------------------------------
    // CHECK: Final state — getNumberOfNodes() and isEmpty()
    // --------------------------------------------------
    printSection("15. Final State");
    cout << "getNumberOfNodes(): " << library.getNumberOfNodes() << endl;
    cout << "getHeight():        " << library.getHeight() << endl;
    cout << "isEmpty():          " << (library.isEmpty() ? "true" : "false") << endl;
    cout << endl << "Final inorder traversal:" << endl;
    library.inorderTraverse(displaySong);

    cout << endl << "========================================" << endl;
    cout << "  All checklist items demonstrated." << endl;
    cout << "========================================" << endl;

    return 0;
}
