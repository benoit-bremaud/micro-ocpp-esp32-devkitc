# Security Policy for `micro-ocpp-esp32-devkitc`

This file documents all security-related decisions, configurations and constraints enforced in this repository. It is intended to ensure long-term project integrity and clarity for all future maintainers and contributors.

---

## Repository Visibility

* **Status**: `Public`
* **Reason**: Required to enable `rulesets` and enforce GitHub security policies (not available for private repositories on free plans).
* **Security Note**: All private keys, credentials, or device-specific secrets must be excluded from the repository. See `env.h` (ignored) and `env.ci.h` (public CI stub).

---

## Branch Protection Rules (`main`)

Enforced via GitHub ruleset:

* All changes to `main` must go through a Pull Request
* Pull Request must receive 1 approval minimum
* Must pass CI status check: `build (pull_request)`
* Must be up to date with `main` before merge
* Applies to administrators
* No direct pushes to `main`

---

## GitHub Actions Restrictions

### Allowed Actions

Only the following official and verified actions are allowed:

```text
actions/checkout@*
actions/setup-python@*
actions/cache@*
```

Any other unlisted action is blocked by default.

### Workflow Permissions (`GITHUB_TOKEN`)

* Read-only by default
* Does not allow GitHub Actions to create or approve pull requests

### External Fork PR Behavior

* PRs from first-time contributors require manual approval before any workflow runs

---

## Artifact and Log Retention

* Logs and build artifacts from CI are retained for 90 days (maximum GitHub retention period)

---

## Installed GitHub Apps

* None currently installed
* Every GitHub App integration will be audited before installation and documented here

---

## Future Security Improvements (Optional)

The following measures may be considered to further improve repository security over time:

* Enforce signed commits to ensure authenticity and authorship validation of all contributions.
* Enable `CODEOWNERS` to define review responsibilities and enforce maintainers’ review on critical files.
* Consider adding a merge queue to enforce sequential merge order and up-to-date branch status.
* Require Two-Factor Authentication (2FA) for all contributors to protect against unauthorized account access.
* Regularly review and rotate secrets to limit long-term exposure of credentials.
* Enable GitHub secret scanning to detect accidental exposure of tokens or sensitive data in commits.
* Conduct periodic security audits to evaluate repository configurations and CI/CD workflows.
* Educate contributors on secure coding practices and GitHub’s security model.

---

## Reporting Vulnerabilities

If you believe you’ve found a security vulnerability in this project:

1. Do not open a GitHub issue or PR.
2. Contact the maintainers privately at: <benoit.bremaud@vev.com>

---

Last updated: 2025-05-27  
Maintainer: Benoît Bremaud

