
#ifndef RANGEVIEWPLUGIN_H
#define RANGEVIEWPLUGIN_H 

#include <QtGui/QtGui>
#include <QtDesigner/QDesignerCustomWidgetInterface>

class RangeViewPlugin : public QObject , public QDesignerCustomWidgetInterface
{
  Q_OBJECT
  Q_INTERFACES(QDesignerCustomWidgetInterface)

 public:
   RangeViewPlugin(QObject *parent = 0);
   virtual ~RangeViewPlugin();

   bool isContainer() const;
   bool isInitialized() const;
   QIcon icon() const;
   QString domXml() const;
   QString group() const;
   QString includeFile() const;
   QString name() const;
   QString toolTip() const;
   QString whatsThis() const;
   QWidget *createWidget(QWidget *parent);
   void initialize(QDesignerFormEditorInterface *core);

 private:
   bool initialized; 
};
#endif
