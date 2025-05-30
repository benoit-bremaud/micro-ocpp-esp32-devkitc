# Atomic Issue Template

## Issue Title Format
`[CATEGORY] Brief descriptive title`

Example: `[INFRA] WebSocket Client Implementation`

## Issue Description Template

\`\`\`markdown
## 🎯 Objective
Brief description of what this issue aims to accomplish.

## 📋 Requirements
- [ ] Requirement 1
- [ ] Requirement 2
- [ ] Requirement 3

## 📝 Technical Details
Detailed technical information, references, or implementation notes.

## 🧩 Tasks
- [ ] Task 1
- [ ] Task 2
- [ ] Task 3
- [ ] Write unit tests
- [ ] Update documentation

## 🔗 Dependencies
- Depends on #XX (if applicable)
- Blocks #YY (if applicable)

## 📊 Acceptance Criteria
- [ ] Criterion 1
- [ ] Criterion 2
- [ ] All tests pass
- [ ] Documentation updated

## 📈 Estimation
Story points: X (1, 2, 3, 5, 8, 13)
\`\`\`

## Example Issue: WebSocket Client Implementation

\`\`\`markdown
## 🎯 Objective
Implement a robust WebSocket client for OCPP communication that handles connections, reconnections, and message exchange with the Central System.

## 📋 Requirements
- [ ] Establish secure WebSocket connections (ws:// and wss://)
- [ ] Handle connection lifecycle (connect, disconnect, reconnect)
- [ ] Implement ping/pong mechanism for connection health
- [ ] Provide message sending and receiving interface
- [ ] Handle connection errors gracefully

## 📝 Technical Details
- Use the WebSockets library by Links2004
- Follow OCPP-J 1.6 specification for message format
- Implement exponential backoff for reconnection attempts
- Store messages in a queue when offline

## 🧩 Tasks
- [ ] Create WebSocketClient class with basic interface
- [ ] Implement connection establishment and authentication
- [ ] Add reconnection logic with exponential backoff
- [ ] Implement message sending with queuing
- [ ] Add message receiving and callback mechanism
- [ ] Implement ping/pong for connection health
- [ ] Add SSL/TLS support for secure connections
- [ ] Write unit tests for all functionality
- [ ] Document the API and usage examples

## 🔗 Dependencies
- Depends on #1 (Project Structure Setup)
- Depends on #2 (WiFi Connection Manager)
- Blocks #10 (OCPP Message Framework)

## 📊 Acceptance Criteria
- [ ] Can establish connection to OCPP server
- [ ] Automatically reconnects after connection loss
- [ ] Successfully sends and receives OCPP messages
- [ ] Handles connection errors without crashing
- [ ] All unit tests pass
- [ ] Memory usage is within acceptable limits
- [ ] Documentation is complete and accurate

## 📈 Estimation
Story points: 8
