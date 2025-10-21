package com.krsna.project.demo.dto;

import java.util.List;

public record ChatRequest(
        String model,
        List<ChatMessage> messages,
        boolean stream,
        Double temperature
) {}

// The rest of the records are in the same file but are NOT public.
// This makes them accessible within the same 'dto' package.
record ChatMessage(String role, String content) {}

record Choice(ChatMessage message) {}

record ChatResponse(List<Choice> choices) {}