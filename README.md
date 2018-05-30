# QSpellWork

**QSpellWork** is an application for searching and viewing information about spells in **World of Warcraft**. Spell information is read from client DBC files. **QSpellWork** works with:

* World of Warcraft (Vanilla)
* The Burning Crusade
* Wrath of the Lich King

This application is written in C++ using the Qt 5 GUI framework.

### How to use scripted filter

**QSpellwork** binds the metaobject to the script engine as `spell` and you can write complex conditions in the JavaScript language. Also binds all enum constants. You can use **inline** or **function** conditions.

Examples

Inline condition:
```javascript
spell.SpellFamilyName == SPELLFAMILY_MAGE && spell.SpellFamilyFlags & 0x1 && spell.hasAura(3)
```

Same as function condition:
```javascript
function() {
    var hasAura = false;
    for (var i = 0; i < 3; i++) {
        if (spell.EffectApplyAuraName(i) == 3) {
            hasAura = true;
            break;
        }
    }
    return spell.SpellFamilyName == SPELLFAMILY_MAGE && spell.SpellFamilyFlags & 0x1 && hasAura;
}
```

You can also use the helper function `hasAura(id)`:

```javascript
function() {
    return spell.SpellFamilyName == SPELLFAMILY_MAGE && spell.SpellFamilyFlags & 0x1 && spell.hasAura(3);
}
```

### Acknowledgements and Thanks

**Chestr aka DiSlord** — for the idea and releasing the source of original SpellWork.
**LordJZ** and **Konstantin** — for releasing the source of C# SpellWork

[![Donate](https://www.paypalobjects.com/en_US/i/btn/btn_donate_LG.gif)](https://www.paypal.me/sidsukana)
