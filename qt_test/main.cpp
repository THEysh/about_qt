#include <QApplication>
#include <QSplitter>
#include <QTreeView>
#include <QTextEdit>

int main(int argc, char *argv[])
{

    tree = QtWidgets.QTreeWidget()
    tree.setColumnCount(2)
    tree.setHeaderLabels(['列1', '列2'])


    parent = QtWidgets.QTreeWidgetItem(tree)
    parent.setText(0, '父节点')
    child1 = QtWidgets.QTreeWidgetItem(parent)
    child1.setText(0, '子节点1')
    child2 = QtWidgets.QTreeWidgetItem(parent)
    child2.setText(0, '子节点2')


    new_text = '新的子节点1'
    child_item = parent.child(0)
    child_item.setText(0, new_text)

    tree.show()

}
