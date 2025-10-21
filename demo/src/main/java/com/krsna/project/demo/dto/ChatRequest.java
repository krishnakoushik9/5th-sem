package com.krsna.project.demo.dto;

import java.util.List;

public record ChatRequest(
        String model,
        List<ChatMessage> messages,
        boolean stream,
        Double temperature
) {
}