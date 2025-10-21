package com.krsna.project.demo.controller;

import com.krsna.project.demo.dto.ChatMessage;
import com.krsna.project.demo.dto.ChatRequest;
import com.krsna.project.demo.service.ChatbotService;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.ResponseBody;
import reactor.core.publisher.Mono;

import java.util.List;

@Controller
public class ChatbotController {

    private final ChatbotService chatbotService;
    // Add logger to the controller
    private static final Logger log = LoggerFactory.getLogger(ChatbotController.class);

    public ChatbotController(ChatbotService chatbotService) {
        this.chatbotService = chatbotService;
    }

    @GetMapping("/")
    public String chatPage() {
        return "index";
    }

    @GetMapping("/mealcali.html")
    public String mealCaliPage(){
        return "mealcali";
    }

    @PostMapping("/chat")
    @ResponseBody
    public Mono<ChatMessage> handleChatRequest(@RequestBody UserInput userInput) {
        String model = "llama3.1-8b";
        List<ChatMessage> messages = List.of(
                new ChatMessage("system", "You are a knowledgeable and supportive nutritionist who gives clear, practical, and science-based diet and health advice."),
                new ChatMessage("user", userInput.message())
        );
        ChatRequest request = new ChatRequest(model, messages, false, 0.7);

        return chatbotService.getChatResponse(request)
                .map(chatResponse -> {
                    // This logic is now safer and checks for nulls and empty lists
                    if (chatResponse.choices() != null && !chatResponse.choices().isEmpty() && chatResponse.choices().get(0).message() != null) {
                        return chatResponse.choices().get(0).message();
                    }
                    // If we get here, the response structure was not what we expected.
                    log.warn("Received a valid response from Cerebras, but it contained no choices or message content.");
                    throw new IllegalStateException("Invalid response structure from API: No valid choices found.");
                })
                // This new logger will catch ANY error, including a NullPointerException from the .map() operator
                .doOnError(error -> log.error("!!! CRITICAL ERROR in controller processing: {}", error.getMessage()));
    }

    public record UserInput(String message) {}
}