#ifndef SWENUMS_H
#define SWENUMS_H

#include <QtCore/QMap>
#include <QtCore/QHash>
#include <QtXml/QDomDocument>

typedef QMap<qint64, QString> Enumerator;
typedef QHash<QString, Enumerator> EnumHash;
typedef QMapIterator<qint64, QString> EnumIterator;

class SWEnums
{
    public:
        SWEnums();
        ~SWEnums();

        EnumHash getEnums() const { return m_enums; }

        Enumerator getSpellFamilies() const { return m_enums["SpellFamily"]; }
        Enumerator getMechanics() const { return m_enums["Mechanic"]; }
        Enumerator getSchools() const { return m_enums["School"]; }
        Enumerator getPowers() const { return m_enums["Power"]; }
        Enumerator getDamageClasses() const { return m_enums["DamageClass"]; }
        Enumerator getPreventionTypes() const { return m_enums["PreventionType"]; }
        Enumerator getSpellMods() const { return m_enums["SpellMod"]; }
        Enumerator getUnitMods() const { return m_enums["UnitMod"]; }
        Enumerator getAuraStates() const { return m_enums["AuraState"]; }
        Enumerator getDispelTypes() const { return m_enums["DispelType"]; }
        Enumerator getItemClasses() const { return m_enums["ItemClass"]; }
        Enumerator getAttributes() const { return m_enums["Attributes"]; }
        Enumerator getAttributesEx1() const { return m_enums["AttributesEx1"]; }
        Enumerator getAttributesEx2() const { return m_enums["AttributesEx2"]; }
        Enumerator getAttributesEx3() const { return m_enums["AttributesEx3"]; }
        Enumerator getAttributesEx4() const { return m_enums["AttributesEx4"]; }
        Enumerator getTargets() const { return m_enums["Target"]; }
        Enumerator getInventoryTypes() const { return m_enums["InventoryType"]; }
        Enumerator getItemSubClassMiscs() const { return m_enums["ItemSubClassMisc"]; }
        Enumerator getItemSubClassArmors() const { return m_enums["ItemSubClassArmor"]; }
        Enumerator getItemSubClassWeapons() const { return m_enums["ItemSubClassWeapon"]; }
        Enumerator getShapeshiftForms() const { return m_enums["ShapeshiftForm"]; }
        Enumerator getCreatureTypes() const { return m_enums["CreatureType"]; }
        Enumerator getTargetFlags() const { return m_enums["TargetFlag"]; }
        Enumerator getSpellEffects() const { return m_enums["SpellEffect"]; }
        Enumerator getSpellAuras() const { return m_enums["SpellAura"]; }

        void loadEnums();

    private:
        EnumHash m_enums;
        QDomDocument m_xmlData;
};

#endif

