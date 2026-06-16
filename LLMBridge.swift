import Foundation
import FoundationModels

@_cdecl("generate_text_from_apple_model")
public func generate_text_from_apple_model(cPrompt: UnsafePointer<CChar>) -> UnsafeMutablePointer<CChar>? {
    let prompt = String(cString: cPrompt)
    var responseText = ""
    
    // Create a semaphore to block the thread while waiting for the async Swift API
    let semaphore = DispatchSemaphore(value: 0)
    
    Task {
        do {
            // Initialize Apple's local LLM session
            let session = LanguageModelSession()
            
            // Await the local inference response
            let response = try await session.respond(to: prompt)
            responseText = response.content
        } catch {
            responseText = "Error running Apple Foundation Model: \(error.localizedDescription)"
        }
        semaphore.signal()
    }
    
    _ = semaphore.wait(timeout: .distantFuture)
    
    // Convert Swift String back to a C-allocated string pointer
    return strdup(responseText)
}
