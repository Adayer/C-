// Fill out your copyright notice in the Description page of Project Settings.


#include "ConversationAssetXmlFactory.h"


#include "XmlFile.h"
#include "UTAD2021/ConversationAsset.h"

UConversationAssetXmlFactory::UConversationAssetXmlFactory()
{
    //... Inicialización de la factoría ...
    SupportedClass = UConversationAsset::StaticClass();
    bCreateNew = false;
    bEditorImport = true;
    Formats.Add(FString("xml;xml conversation"));
}

UObject* UConversationAssetXmlFactory::FactoryCreateFile(UClass* InClass, UObject* InParent, FName InName,
  EObjectFlags Flags, const FString& Filename, const TCHAR* Parms, FFeedbackContext* Warn, bool& bOutOperationCanceled)
{
  FXmlFile xmlFile(Filename, EConstructMethod::ConstructFromFile);
  FXmlNode* root = xmlFile.GetRootNode();
  if (!root) { return nullptr; }

  UConversationAsset* newAsset = NewObject<UConversationAsset>(InParent, InClass, InName, Flags);

  FString conversationName = root->GetAttribute("name");
  newAsset->Name = conversationName;
  FXmlNode const* linesNode = root->FindChildNode("Lines");
  if (linesNode)
  {
    TArray<FXmlNode*> const& linesChildren = linesNode->GetChildrenNodes();
    for (const FXmlNode* lineNode : linesChildren)
    {
      FConversationLine& line = newAsset->Lines.AddDefaulted_GetRef();
      FString strDuration = lineNode->GetAttribute("duration");
      if (strDuration.IsNumeric())
      {
        line.Duration = FCString::Atof(*strDuration);
      }
      FString strColor = lineNode->GetAttribute("color");
      if (!strColor.IsEmpty())
      {
        line.Color = FColor::FromHex(strColor);
      }
      FString strOffset = lineNode->GetAttribute("offset");
      if (strOffset.IsNumeric())
      {
        line.Offset = FCString::Atoi(*strOffset);
      }
      line.Text = lineNode->GetContent();
    }
  }
  return newAsset;
}
