package com.krsna.project.demo.service;

import com.krsna.project.demo.dto.ChatRequest;
import com.krsna.project.demo.dto.ChatResponse;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.stereotype.Service;
import org.springframework.web.reactive.function.client.WebClient;
import reactor.core.publisher.Mono;

@Service
public class ChatbotService {

    private final WebClient webClient;
    // Add this logger instance
    private static final Logger log = LoggerFactory.getLogger(ChatbotService.class);

    public ChatbotService(WebClient cerebrasWebClient) {
        this.webClient = cerebrasWebClient;
    }

    public Mono<ChatResponse> getChatResponse(ChatRequest request) {
        return webClient.post()
                .bodyValue(request)
                .retrieve()
                .bodyToMono(ChatResponse.class)
                // This new line will log the specific error if the API call fails
                .doOnError(error -> log.error("ERROR calling Cerebras API: {}", error.getMessage()));
    }
}