#include "outliner_delegate.h"

#include "../../types.h"
#include "../../proxyid.h"
#include "outliner_model.h"
#include <QLineEdit>

// Special 6
//============================================================
saklib::Qtlib::Outliner_Delegate::Outliner_Delegate(QWidget* parent):
    QItemDelegate(parent)
{
}
saklib::Qtlib::Outliner_Delegate::~Outliner_Delegate() = default;

// Virtual Overrides
//============================================================
QWidget* saklib::Qtlib::Outliner_Delegate::createEditor(QWidget* parent, QStyleOptionViewItem const& /*option*/, QModelIndex const& index) const
{
    // Only continue if the index is valid and not nonsense
    if (!index.isValid() && index.column() == 0)
    {
        return nullptr;
    }

    // Get the proxy
    auto indexid = ProxyID::unpack(index.internalId());

    // if it's the root
    if (!indexid.is_valid())
    {
        return nullptr;
    }
    // else it's an Element
    else if (indexid.is_element())
    {
        //auto editor = std::make_unique<QLineEdit>(parent);
        return std::make_unique<QLineEdit>(parent).release();
    }
    // else it's an Attribute
    else if (indexid.is_attribute())
    {
        return nullptr;
    }

    // No conditions met
    return nullptr;
}
void saklib::Qtlib::Outliner_Delegate::setEditorData(QWidget* editor, QModelIndex const& index) const
{
    // Only continue if the index is valid and not nonsense
    if (!index.isValid() && index.column() == 0)
    {
        return;
    }

    // Get the proxy
    auto indexid = ProxyID::unpack(index.internalId());

    // if it's the root
    if (!indexid.is_valid())
    {
        return;
    }
    // else it's an Element
    else if (indexid.is_element())
    {
        // This is the only bit that will be edited..

        // Cast to editor type
        auto true_editor = dynamic_cast<QLineEdit*>(editor);

        // Get the data at index
        auto index_data = index.model()->data(index);

        // Set the editor data
        true_editor->setText(index_data.toString());

        return;
    }
    // else it's an Attribute
    else if (indexid.is_attribute())
    {
        return;
    }

    // No conditions met
}
void saklib::Qtlib::Outliner_Delegate::setModelData(QWidget* editor, QAbstractItemModel* model, QModelIndex const& index) const
{
    // Only continue if the index is valid and not nonsense
    if (!index.isValid() && index.column() == 0)
    {
        return;
    }

    // Get the proxy
    auto indexid = ProxyID::unpack(index.internalId());

    // if it's the root
    if (!indexid.is_valid())
    {
        return;
    }
    // else it's an Element
    else if (indexid.is_element())
    {
        // This is the only bit that will be edited..

        // Cast to editor type
        auto true_editor = dynamic_cast<QLineEdit*>(editor);

        // Get the data at index
        auto editor_data = QVariant(true_editor->text());

        // Set the model data
        model->setData(index, editor_data);

        return;
    }
    // else it's an Attribute
    else if (indexid.is_attribute())
    {
        return;
    }

    // No conditions met
}
void saklib::Qtlib::Outliner_Delegate::updateEditorGeometry(QWidget *editor, QStyleOptionViewItem const& option, QModelIndex const& /*index*/) const
{
    editor->setGeometry(option.rect);
}
