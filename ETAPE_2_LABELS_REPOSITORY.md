# Étape 2 : Créer les Labels dans le Repository

## 📋 Actions dans votre repository

### 1. Aller dans les Settings du repository

- `https://github.com/benoit-bremaud/micro-ocpp-esp32-devkitc/settings`
- Cliquez sur **"Labels"** dans le menu de gauche

### 2. Supprimer les labels par défaut (optionnel)

- Vous pouvez garder : `bug`, `enhancement`, `documentation`
- Supprimer : `good first issue`, `help wanted`, `question`, etc.

### 3. Créer les nouveaux labels

#### Labels par Type

| Nom | Couleur | Description |
|-----|---------|-------------|
| `type:feat` | `#0e8a16` | Nouvelle fonctionnalité |
| `type:fix` | `#d73a4a` | Correction de bug |
| `type:docs` | `#0075ca` | Documentation |
| `type:chore` | `#fef2c0` | Maintenance et configuration |
| `type:test` | `#f9d0c4` | Tests unitaires et intégration |

#### Labels par Domaine OCPP

| Nom | Couleur | Description |
|-----|---------|-------------|
| `ocpp:infrastructure` | `#5319e7` | Infrastructure technique de base |
| `ocpp:core` | `#b60205` | Fonctionnalités OCPP obligatoires |
| `ocpp:remote` | `#fbca04` | Contrôle à distance |
| `ocpp:firmware` | `#0052cc` | Gestion firmware et diagnostics |

#### Labels par Priorité

| Nom | Couleur | Description |
|-----|---------|-------------|
| `priority:critical` | `#b60205` | Critique - bloque le développement |
| `priority:high` | `#d93f0b` | Haute - nécessaire pour MVP |
| `priority:medium` | `#fbca04` | Moyenne - important mais pas urgent |
| `priority:low` | `#0e8a16` | Basse - amélioration future |

## 💡 Comment créer un label

1. Cliquez sur **"New label"**
2. Entrez le **nom** exact (ex: `type:feat`)
3. Entrez la **couleur** (ex: `#0e8a16`)
4. Entrez la **description**
5. Cliquez sur **"Create label"**

## ✅ Résultat attendu

Vous devriez avoir 12 nouveaux labels organisés par catégorie, prêts à être utilisés pour les issues.
